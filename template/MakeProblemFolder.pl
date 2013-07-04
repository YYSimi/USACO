#!/usr/bin/perl -w

if (!defined($ARGV[1])) {
    usage();
    exit;
}

$PlaceholderString="PROGNAME";
$ProgramName=$ARGV[0];
$ChapterName=$ARGV[1];
if (!($ChapterName =~ /^ch/)) {$ChapterName = "ch".$ChapterName} #append "ch" to the front if I forgot to do so. 
$BasePath="/home/youlian/Documents/CS/USACO";
$FullPath=$BasePath."/".$ChapterName;

@FilesToProcess = ("makefile", "template.cpp");
@RenameFilesTo = ("makefile", "$ProgramName.cpp");

if(-d $FullPath){
    print "Found Directory $FullPath\n";
}
else {
    print "Directory $FullPath not found.  Creating $FullPath.\n";
    mkdir $FullPath;
}

$FullPath=$FullPath."/".$ProgramName;

if(-d $FullPath){
    print "Found Directory $FullPath\n";
}
else {
    print "Directory $FullPath not found.  Creating $FullPath.\n";
    mkdir $FullPath;
}


foreach my $i (0 .. @FilesToProcess-1) {
    print "Opening $FilesToProcess[$i] and $RenameFilesTo[$i]\n";
    open(F1, $FilesToProcess[$i]);
    open(F2, ">".$FullPath."/".$RenameFilesTo[$i]);
    while($line = <F1>){
        #print "Processing: " . $line;
        $line =~ s/$PlaceholderString/$ProgramName/g;
        #print "Convert: " . $line;
        print F2 $line;
    }
}

sub usage{
    print "$0 Usage:\n";
    print "\t $0 [problemname] [chapter] -- Creates a new directory for the problem in the given chapter.  Populates this directory with a makefile and c++ template.\n";
}
