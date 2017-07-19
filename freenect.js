const binding = require('bindings')('freenect');

const LedOptions = {
  OFF: 0,
  GREEN: 1,
  RED: 2,
  YELLOW: 3,
  BLINK_GREEN: 5,
  BLINK_RED_YELLOW: 6
};

module.exports = {
  Freenect: binding.Freenect,
  LedOptions,
};
