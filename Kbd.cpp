// ---   *   ---   *   ---
// KBD
// Handles them keys
//
// LIBRE SOFTWARE
// Licensed under GNU GPL3
// be a bro and inherit
//
// CONTRIBUTORS
// lyeb,

// ---   *   ---   *   ---
// deps

  #include "Kbd.hpp"

// ---   *   ---   *   ---
// cstruc blank

Kbd::Kbd(void) {

  Cback def[3]={
    &Kbd::noop,
    &Kbd::noop,
    &Kbd::noop

  };

  Key empty={0};

  for(uint8_t i=0;i<NUM_KEYS;i++) {
    m_keys.push_back(empty);
    this->remap(i,&def[0]);

    m_keys[i].active=0;

  };

};

// ---   *   ---   *   ---
// ^initialize from set

// ---   *   ---   *   ---
// adds new event to stack
// or update existing

void Kbd::push(uint32_t keyid,bool rel) {

  Key& key=m_keys[keyid];

  if(! key.active) {
    return;

  };

  if(

     (! rel)
  && (! (key.state & 0b111))

  ) {

    m_events.push_back(keyid);
    key.is_tap=1;

  } else if(rel && (key.state & 0b011)) {
    key.is_hel=0;
    key.is_rel=1;

  } else if((! rel) && (! key.is_rel)) {
    key.is_tap=0;
    key.is_hel=1;

  };

};

// ---   *   ---   *   ---
// goes through event stack

void Kbd::run(void) {

  uint32_t    i=0;
  Kbd::Events rem;

  for(auto& keyid : m_events) {

    Key& key=m_keys[keyid];

    // on press
    if(key.is_tap) {
printf("TAP ");
      key.on_tap(key);

      key.is_tap=0;
      key.is_hel=! key.is_rel;

    // ^key is held from last frame
    } else if(key.is_hel) {
printf("HEL ");
      key.on_hel(key);

      key.reptime+=
        key.reptime > uint64_t(-1);

    };

    // ^key is let go
    if(key.is_rel) {
printf("REL ");
      key.on_rel(key);

      key.reptime=0;
      key.state&=~ 0b111;

      rem.push_back(i);

    };

    i++;

  };

  this->pop(rem);

};

// ---   *   ---   *   ---
// set callbacks for key

void Kbd::remap(uint32_t keyid,Kbd::Cback* cbacks) {

  Key& key=m_keys[keyid];

  // default blanks to do nothing
  for(uint8_t i=0;i<3;i++) {
    if(cbacks[i] == NULL) {
      cbacks[i]=&Kbd::noop;

    };

  };

  // set callbacks
  key.on_tap = cbacks[0];
  key.on_hel = cbacks[1];
  key.on_rel = cbacks[2];

  // reset state
  key.state  = 0x00;
  key.active = 1;

};

// ---   *   ---   *   ---

