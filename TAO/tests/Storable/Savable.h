// $Id$

#include "tao/Storable_Base.h"

#include "ace/SString.h"

namespace TAO
{
  class Storable_Factory;
}

class Storable_Exception
{
 public:

  Storable_Exception(TAO::Storable_Base::Storable_State state)
    : stream_state_(state)
  {
  }

  TAO::Storable_Base::Storable_State get_state ()
    {
      return stream_state_;
    }

 private:
  TAO::Storable_Base::Storable_State stream_state_;
};

/// A simple class to use for testing whose contents
/// are to be persisted. It has attributes for each basic
/// type that can be saved.
/// There are two attributes for each type so that
/// one process can write one attribute of the same
/// type while another process reads another attribute
/// of the same type.
class Savable
{
 public:
  Savable (TAO::Storable_Factory & storable_factory);

  ~Savable ();

  void string_set (int index, const ACE_CString &s);
  const ACE_CString & string_get (int index);

  void int_set (int index, int i);
  int int_get (int index);

  void unsigned_int_set (int index, unsigned int ui);
  unsigned int unsigned_int_get (int index);

  void bytes_set (int index, int size, char * bytes);
  int bytes_get (int index, char * bytes);

  bool is_loaded_from_stream ();

 private:
  TAO::Storable_Factory & storable_factory_;
  bool loaded_from_stream_;
  time_t last_changed_;
  void read (TAO::Storable_Base & stream);
  void write (TAO::Storable_Base & stream);

  ACE_CString string_[2];
  int i_[2];
  unsigned int ui_[2];

  static const int bytes_size_max;
  int bytes_size_[2];
  char * bytes_[2];

  friend class Savable_File_Guard;
};

