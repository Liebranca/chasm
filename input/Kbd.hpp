#ifndef __5E_KBD_H__
#define __5E_KBD_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"
  #include "input/Kbdlay.hpp"

// ---   *   ---   *   ---
// info

class Kbd {

friend class Event;

public:

  VERSION   "v0.00.3b";
  AUTHOR    "IBN-3DILA";

  cx8 NUM_KEYS=0x66;

// ---   *   ---   *   ---
// helpers

  struct Key {

    // event type
    union {
      struct {
        uint8_t is_tap: 1;
        uint8_t is_hel: 1;
        uint8_t is_rel: 1;

        uint8_t active: 1;

      };uint8_t state;

    };

    // ^per-event callbacks
    union {
      struct {
        nihil on_tap;
        nihil on_hel;
        nihil on_rel;

      };nihil cbacks[3];

    };

    uint64_t reptime;

  };

  typedef std::vector<Key> Keys;
  typedef std::vector<uint32_t> Events;

// ---   *   ---   *   ---
// passed to cstruc/remap

  struct Key_Bld {
    uint8_t id;
    nihil   cbacks[3];

  };

  typedef std::vector<Key_Bld> Keyset;
  static Keyset DEFKEYS;

// ---   *   ---   *   ---
// attrs

private:

  Keys   m_keys;
  Events m_events;

// ---   *   ---   *   ---
// guts

  // remove element(s) from event stack
  inline void pop(Events& rem) {
    for(auto i : rem) {
      m_events.erase(m_events.begin()+i);

    };

  };

  // ^remove all
  inline void clear(void) {
    m_events.erase(
      m_events.begin(),
      m_events.end()

    );

  };

// ---   *   ---   *   ---
// iface

public:

  // cstruc
  Kbd(void);
  ~Kbd(void) {};

  // goes through event stack
  void run(void);

  // adds new event to stack
  // or update existing
  void push(uint32_t keyid,bool rel);

  // set callbacks for key
  void remap(uint32_t keyid,nihil* cbacks);

  // ^whole set
  inline void set_remap(Keyset& keys) {
    for(auto& key : keys) {
      this->remap(key.id,&key.cbacks[0]);

    };

  };

  // remove key from active set
  inline void unmap(uint32_t keyid) {
    m_keys[keyid].active=0;

  };

  // ^whole
  inline void set_unmap(void) {
    for(uint8_t i=0;i<NUM_KEYS;i++) {
      this->unmap(i);

    };

  };

  // get handle to specific key
  inline Key& key(uint32_t keyid) {
    return m_keys[keyid];

  };

};

// ---   *   ---   *   ---
#endif // __5E_KBD_H__
