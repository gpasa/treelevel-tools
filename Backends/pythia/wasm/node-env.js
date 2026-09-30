// Prototype Node : l'environnement du shell passe au WebAssembly (PYTHIA8DATA, entre autres), ce qu'Emscripten
// ne fait pas de lui-même.
Module['preRun'] = (Module['preRun'] || []).concat([function () {
  for (var k in process.env) ENV[k] = process.env[k];
}]);
