#!/usr/bin/perl

  use v5.36.0;
  use strict;
  use warnings;

  use lib $ENV{'ARPATH'}.'/lib/sys/';
  use Shb7;

  use lib $ENV{'ARPATH'}.'/lib/';
  use Avt;

# ---   *   ---   *   ---

Avt::set_config(

  name=>'chasm',
  build=>'ar:chasm',

  incl=>[qw(bitter)],
  libs=>[qw(bitter SDL2 SDL2main GL GLEW)],

  # regenerate layout files
  # if updates detected
  pre_build=>q[

    my $path = dirof(__FILE__);
    my $ex   = "$path/bin/genlay";

    ! Shb7::moo("$path/Kbdlay.hpp","$ex")
    or say {*STDERR} `$ex`;

  ],

);

Avt::scan();
Avt::config();
Avt::make();

# ---   *   ---   *   ---
1; # ret
