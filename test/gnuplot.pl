#! /usr/bin/perl
# -*- cperl -*-
#
# Copyright (C) 2010 Tomash Brechko.  All rights reserved.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
use warnings;
use strict;

=head1 NAME

gnuplot.pl - Generate input file for B<gnuplot>

=head1 SYNOPSIS

  gnuplot.pl FILE FROM TO STEP REPEAT TEST...
  gnuplot.pl --help

=head2 example

  gnuplot.pl test.log 2500 100000 2500 1 test/cuckoo_hash test/std-map

=head1 DESCRIPTION

For element count from I<FROM> to I<TO> with step I<STEP> run each
I<TEST> as

  TEST 0 count REPEAT

(zero is a seed value).  Accumulate data from each run, and output it
to I<FILE> in table format suitable for B<gnuplot>.

Interrupting (with C-c, SIGINT) the script at any moment will save to
I<FILE> all the data accumulated thus far.

=cut

use Pod::Usage;

pod2usage({ -verbose => 2 }) if @ARGV == 1 && $ARGV[0] eq "--help";
pod2usage("Not enough arguments\n") if @ARGV < 6;
my @nonnum = grep { /(\D)/ } @ARGV[1..4];
pod2usage("Not a number: $nonnum[0]\n") if @nonnum;

my ($file, $from, $to, $step, $repeat, @tests) = @ARGV;

# Two argument form will open STDOUT when $file is "-".
open(my $out, ">$file")
  or die "open(>$file): $!";

my @names = map { m|([^/]+)$| } @tests;
my @aspects = map { /^([^:]+)/ } qx/$tests[0] 0 0 $repeat/;


my $max = length($to);
foreach (@aspects) {
    $max = length if $max < length;
}
my $format = join(" ", "%${max}s:", map { "%" . length($_) . "s" } @names);
$format .= "\n";
$max += 1 + @names;
$max += length for @names;

my $interrupted;
$SIG{INT} = sub { $interrupted = 1 };

my @data;
STEP:
for (my $count = $from; $count <= $to; $count += $step) {
    my @columns;
    foreach my $test (@tests) {
        last STEP if $interrupted;

        my @rows = map { /^[^:]+: (\S+)/ } qx/$test 0 $count $repeat/;
        for (my $i = 0; $i < @rows; ++$i) {
            push @{$columns[$i]}, $rows[$i];
        }
    }
    last STEP if $interrupted;

    print "-" x $max, "\n";
    printf $format, $count, @names;
    for (my $i = 0; $i < @columns; ++$i) {
        push @{$data[$i]}, $columns[$i];
        printf $format, $aspects[$i], @{$columns[$i]};
    }
}

print $out <<EOF;
# Generated with gnuplot.pl @ARGV
#
# You can plot the contents of this file with gnuplot like this:
#
#   (shell)\$ gnuplot
#   gnuplot> file = '/path/to/this/file'
#   gnuplot> call file file INDEX
#
# Giving file twice is not a typo.  INDEX is in the range 0-$#aspects.
# Corresponding aspects are listed below:

@{[ join "\n", map { "aspect$_ = '$aspects[$_]'" } 0 .. $#aspects ]}

file = \$0
index = \$1

sindex = "" . index
set macros
set key left top title aspect\@sindex
plot file @{[
  join(", \\\n  '' ",
       map({ "index index using 1:$_ title '$names[$_ - 2]' with lines" }
           2 .. $#names + 2)) ]}

exit

EOF

foreach my $aspect (@aspects) {
    print $out "# $aspect\n";
    print $out "# count @names\n";
    my $data = shift @data;
    my $count = $from;
    foreach my $row (@$data) {
        print $out "$count @$row\n";
        $count += $step;
    }
    print $out "\n\n";
}

close($out)
  or die "close(>$file): $!";

print "gnuplot data saved to $file\n";
