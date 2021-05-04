#!/usr/bin/perl -w

# Author: Jacob Cappi
# Email : jc0199@uah.edu
# Date  : 2021.04.22
# File  : delc.pl
# Usage : perl delc.pl foo/*.bar

use warnings;
use strict;

my @file_list;
my $input;

if (@ARGV){
    @file_list = @ARGV;
}

else{
    print ("Error: no args\n");
    print ("Delc: Use: perl delc.pl args\n");
    exit 1;
}

my $file_type = ""; # String that stores the file type for printing
my @file_for_deletion; # Array of file list that are marked for deletion


foreach (@file_list){
    if (-d $_){ # if dir
        $file_type = "dir";
    }
    elsif (-f $_){ # if file
        $file_type = "file";
    }
    else{ # was checking permissions earlier, but why not
        print "no such file or dir\n";
    }

    print "delete $file_type: $_? [y,q]: ";
    $input = <STDIN>; 
    chomp $input; #removes new line

# lc is case insensitive
    if( lc($input) eq "y" ){
        push @file_for_deletion, $_;
    }
    elsif( lc($input) eq "q"){
        last;
    }
}


my $numDeleted = 0;

print "\nDelete: ";
print "\n*--------------------------*\n";
foreach (@file_for_deletion){
    print "$_ \n";
}
print "*--------------------------*\n";

print "Complete all deletions? [y]: ";
$input = <STDIN>;
chomp $input;

if ( lc($input) eq "y") {
    foreach (@file_for_deletion){
        $_ =~ s/ /\\ /g ; # basic regular expression to handle spaces with rm
        print $_, "\n";
        `rm -rf $_`;
        $numDeleted++;
    }
}

if ($numDeleted == 0){
    print "Nothing has been deleted\n";
}
else{
    print "Delete Successful\n";
}

exit 0;
