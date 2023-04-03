#ifndef __5E_KBD_H__
#define __5E_KBD_H__

// ---   *   ---   *   ---
// deps

  #include "bitter/kvrnel/Style.hpp"

// ---   *   ---   *   ---
// info

class Kbd {

friend class Event;

public:

  VERSION   "v0.00.1b";
  AUTHOR    "IBN-3DILA";

// ---   *   ---   *   ---
// helpers

  struct Key;
  typedef void (*Cback) (Key& key);

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
        Cback on_tap;
        Cback on_hel;
        Cback on_rel;

      };Cback cbacks[3];

    };

    uint64_t reptime;

  };

  typedef std::vector<Key> Keys;
  typedef std::vector<uint32_t> Events;

  // empty callback
  static void noop(Key& key) {};

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
  void remap(uint32_t keyid,Cback* cbacks);

  // remove key from active set
  inline void unmap(uint32_t keyid) {
    m_keys[keyid].active=0;

  };

  inline Key& key(uint32_t keyid) {
    return m_keys[keyid];

  };

};

// ---   *   ---   *   ---
#endif // __5E_KBD_H__
