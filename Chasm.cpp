// ---   *   ---   *   ---
// CHASM
// It drags you in
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "Chasm.hpp"

// ---   *   ---   *   ---
// ugly singleton stuff

CHASM Chasm;

// makes escape kill all
// chasm windows by default
Kbd::Keyset Kbd::DEFKEYS {

  {Keysets::escape,{

    NULL,
    NULL,

    &chasm_exit

  }}

};

// ---   *   ---   *   ---
// cstruc

void CHASM::nit(
  Win::Desc&   desc,
  Kbd::Keyset& keys

) {

  win.nit(desc);

  auto& kbd=ev.get_kbd();
  kbd.set_remap(keys);

};

// ---   *   ---   *   ---
