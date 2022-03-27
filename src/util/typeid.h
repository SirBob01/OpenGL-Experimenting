#ifndef TYPEID_H_
#define TYPEID_H_

// Container for storing a list of template types
template <typename... Type> struct TypeList {};

// Methods for generating unique type IDs
class TypeID {
    unsigned id_counter_;

  public:
    TypeID();

    template <typename T> inline unsigned get_id() {
        static const unsigned id = id_counter_++;
        return id;
    }
};

#endif