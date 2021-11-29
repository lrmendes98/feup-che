#!perl -w
# this is a perl script

# a PERL script to extract power and energy figues from PowerLog3.0
#
#

#------------- MAIN -------------
#use strict; 
#use warnings;

if(@ARGV == 0) {
 #   die "usage: extract [<file>]\n";
}

$input_file = $ARGV[0];

$output_file1 = "report.csv";
open(STUFF2, "> $output_file1") || die "Cannot open $output_file1 for writing.";
print STUFF2 "Opt.,Exec. Time(s),Average Freq. (GHz),Average Power Dissipation(W),Energy Consumption (J)\n";

my @inputs = ("autovect_o1", "autovect_os", "autovect_o2", "autovect_o2_omp","autovect_o3_wvec", "autovect_o3", "autovect_ofast", "autovect_o3_wvec_omp", "autovect_o3_omp", "autovect_ofast_omp", "autovect_ofast_1", "autovect_ofast_1_omp");


foreach $name ( @inputs ) {

$input_file = $name.".csv";


open(STUFF1, $input_file) || die "Cannot open $input_file for read.";

print "Extracting from file...$input_file\n";

while($line=<STUFF1>) {
 
 if($line =~ m/^Measured\sRDTSC\sFrequency\s\(GHz\)\s=\s(\d+\.\d+)/) {
    $Freq=$1;
    print "---- $Freq (GHz)\n";
  } 
  elsif($line =~ m/^Average\sProcessor\sPower_0\s\(Watt\)\s=\s(\d+\.\d+)/) {
    $Power=$1;
    print "---- $Power (W)\n";
  } 
  elsif($line =~ m/^Cumulative\sProcessor\sEnergy_0\s\(Joules\)\s=\s(\d+\.\d+)/) {
    $Energy=$1;
    print "---- $Energy (J)\n";
  } 
  elsif($line =~ m/^Total\sElapsed\sTime\s\(sec\)\s\=\s(\d+\.\d+)/) {
    $TotalExec=$1;
    print "---- $TotalExec (sec)\n";
  } 
#  Measured RDTSC Frequency (GHz) = 1.992
#  Cumulative Processor Energy_0 (Joules) = 146.988464
#Cumulative Processor Energy_0 (mWh) = 40.830129
#Average Processor Power_0 (Watt) = 4.656026  
}

close(STUFF1);
print STUFF2 "$name,$TotalExec,$Freq,$Power,$Energy\n";

}

close(STUFF2);

exit(1);
#------------- END MAIN -------------