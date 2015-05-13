/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2015 NAN contributors
 *
 * MIT License <https://github.com/iojs/nan/blob/master/LICENSE.md>
 ********************************************************************/

const test     = require('tap').test
    , testRoot = require('path').resolve(__dirname, '..')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'gc' });

test('gc', function (t) {
  t.plan(3);

  t.type(bindings.hook, 'function');
  t.type(bindings.check, 'function');

  bindings.hook();
  gc();
  t.ok(bindings.check());
});
