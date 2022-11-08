#include "soro/infrastructure/graph/type.h"

#include "utl/verify.h"

#include "soro/infrastructure/parsers/iss/iss_string_literals.h"
#include "soro/utls/string.h"

namespace soro::infra {

using namespace utls;

type get_type(const char* const str) {
  switch (str_hash(str)) {
    // simple elements
    case str_hash(KM_JUMP_END):
    case str_hash(KM_JUMP_START): return type::KM_JUMP;
    case str_hash(LINE_SWITCH_ZERO):
    case str_hash(LINE_SWITCH_ONE):
      return type::LINE_SWITCH;
      // end elements
    case str_hash(BUMPER): return type::BUMPER;
    case str_hash(BORDER): return type::BORDER;
    case str_hash(TRACK_END):
      return type::TRACK_END;
      // track elements
    case str_hash(APPROACH_SIGNAL_RISING):
    case str_hash(APPROACH_SIGNAL_FALLING): return type::APPROACH_SIGNAL;
    case str_hash(MAIN_SIGNAL_FALLING):
    case str_hash(MAIN_SIGNAL_RISING): return type::MAIN_SIGNAL;
    case str_hash(PROTECTION_SIGNAL_FALLING):
    case str_hash(PROTECTION_SIGNAL_RISING): return type::PROTECTION_SIGNAL;
    case str_hash(ROUTE_EOTD_FALLING):
    case str_hash(ROUTE_EOTD_RISING):
    case str_hash(SIGNAL_EOTD_FALLING):
    case str_hash(SIGNAL_EOTD_RISING): return type::EOTD;
    case str_hash(SPECIAL_SPEED_LIMIT_END_FALLING):
    case str_hash(SPECIAL_SPEED_LIMIT_END_RISING):
    case str_hash(SPEED_LIMIT_RISING):
    case str_hash(SPEED_LIMIT_FALLING): return type::SPEED_LIMIT;
    case str_hash(TUNNEL): return type::TUNNEL;
    case str_hash(HALT_FREIGHT_FALLING):
    case str_hash(HALT_FREIGHT_RISING):
    case str_hash(HALT_PASSENGER_LEFT_RISING):
    case str_hash(HALT_PASSENGER_LEFT_FALLING):
    case str_hash(HALT_PASSENGER_RIGHT_RISING):
    case str_hash(HALT_PASSENGER_RIGHT_FALLING):
    case str_hash(HALT_PASSENGER_BOTH_RISING):
    case str_hash(HALT_PASSENGER_BOTH_FALLING):
    case str_hash(HALT_PASSENGER_RIGHT_LEFT_FALLING):
    case str_hash(HALT_PASSENGER_RIGHT_LEFT_RISING): return type::HALT;
    case str_hash(SLOPE): return type::SLOPE;
    case str_hash(RUNTIME_CHECKPOINT):
      return type::RUNTIME_CHECKPOINT;
      // switches
    case str_hash(SWITCH_START):
    case str_hash(SWITCH_STEM):
    case str_hash(SWITCH_BRANCH_LEFT):
    case str_hash(SWITCH_BRANCH_RIGHT):
      return type::SIMPLE_SWITCH;
      // crosses & cross switches
    case str_hash(CROSS_START_LEFT):
    case str_hash(CROSS_END_LEFT):
    case str_hash(CROSS_START_RIGHT):
    case str_hash(CROSS_END_RIGHT):
    case str_hash(CROSS_SWITCH_START_LEFT):
    case str_hash(CROSS_SWITCH_END_LEFT):
    case str_hash(CROSS_SWITCH_START_RIGHT):
    case str_hash(CROSS_SWITCH_END_RIGHT): return type::CROSS;
    case str_hash(CTC_BLOCK_SIGN_RISING):
      // ct
    case str_hash(CTC_BLOCK_SIGN_FALLING):
    case str_hash(CTC_START_FALLING):
    case str_hash(CTC_END_FALLING):
    case str_hash(CTC_START_RISING):
    case str_hash(CTC_END_RISING):
      return type::CTC;
      // ignore these  for the moment
    default:
    case str_hash(PICTURE_POINT):
    case str_hash(BRAKE_PATH_FALLING):
    case str_hash(BRAKE_PATH_RISING):
    case str_hash(LEVEL_CROSSING):
    case str_hash(ENTRY):
    case str_hash(LINE_CLASS):
    case str_hash(TRACK_NAME): return type::INVALID;
  }
}

type get_type(std::string const& str) { return get_type(str.data()); }

std::string get_type_str(type const& t) {
  switch (t) {
    case type::INVALID: return "invalid";
    case type::BUMPER: return "bumper";
    case type::BORDER: return "border";
    case type::TRACK_END: return "track_end";
    case type::SIMPLE_SWITCH: return "simple_switch";
    case type::APPROACH_SIGNAL: return "as";
    case type::MAIN_SIGNAL: return "ms";
    case type::PROTECTION_SIGNAL: return "ps";
    case type::EOTD: return "eotd";
    case type::SPEED_LIMIT: return "spl";
    case type::TUNNEL: return "tunnel";
    case type::HALT: return "hlt";
    case type::RUNTIME_CHECKPOINT: return "rtcp";
    case type::KM_JUMP: return "km_jump";
    case type::LINE_SWITCH: return "line_switch";
    case type::SLOPE: return "slope";
    case type::CROSS: return "cross";
    case type::CTC: return "ctc";
  }
  throw utl::fail("No type string found in infrastructure element");
}

}  // namespace soro::infra