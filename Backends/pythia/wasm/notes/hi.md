मॉड्यूल का संस्करण: **$MODULE** — Pythia **$PYTHIA_VERSION**, TreeLevel Tools $MODULE के साझा ड्राइवर के साथ
WebAssembly में संकलित। यह पृष्ठ हमेशा एक ही नाम रखता है: iPad पर TreeLevel (1.4 और उसके बाद के संस्करण) यहीं से
नवीनतम संस्करण लेता है, `module.json` में उसकी संख्या पढ़कर उसे अपनी सेटिंग्स में दिखाता है, नया संस्करण प्रकाशित
होने पर अद्यतन का प्रस्ताव देता है, और हर फ़ाइल को उस फ़िंगरप्रिंट से जाँचता है जो `module.json` उसके लिए देता है।
ऐप मॉड्यूल को एक वेब व्यू में चलाता है, कहीं कुछ भी भेजे बिना।

यह मॉड्यूल क्या कर सकता है: `$FEATURES`। "spacetime": पार्टनों और हैड्रॉनों को अन्योन्यक्रिया क्षेत्र में स्थित
करना, जिसे TreeLevel फेम्टोमीटर पर दिखाता है।

| फ़ाइल | भूमिका |
|---|---|
| `module.json` | मॉड्यूल और Pythia का संस्करण, यह क्या कर सकता है, हर फ़ाइल का फ़िंगरप्रिंट |
| `treelevel-pythia-web.wasm`, `.js` | Pythia $PYTHIA_VERSION और ड्राइवर, WebAssembly में |
| `runner.js` | TreeLevel का एक कार्य चलाता है: योजना, भाग, विलय |
| `leptons.pack` | Pythia के आँकड़े (xmldoc, tunes, setups) — लेप्टॉन किरणपुंज |
| `pdfdata.pack` | पार्टन घनत्व — हैड्रॉन किरणपुंज, वैकल्पिक |
| `$SOURCES` | Pythia $PYTHIA_VERSION का स्रोत कोड, जैसा वह pythia.org पर प्रकाशित है |
| `COPYING.pythia8` | Pythia का लाइसेंस (GPL v2 या उसके बाद का) |

iPad पर TreeLevel 1.3 अपना मॉड्यूल
[ipad-pythia-8.318](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia-8.318) से डाउनलोड करता है,
जिसके फ़िंगरप्रिंट उसमें स्थिर हैं: वह पृष्ठ नहीं बदलता।

**Pythia 8 और उसके लेखक।** Pythia 8 © Torbjörn Sjöstrand और Pythia सहयोग-समूह —
[pythia.org](https://pythia.org) — का है, और GPL v2 या उसके बाद के संस्करण के अंतर्गत वितरित है। इस मॉड्यूल की सारी
भौतिकी उन्हीं की है। यदि आप इससे प्राप्त कोई परिणाम प्रकाशित करते हैं, तो उद्धृत करें: C. Bierlich et al.,
"A comprehensive guide to the physics and usage of PYTHIA 8.3", *SciPost Phys. Codebases* 8 (2022),
[arXiv:2203.11601](https://arxiv.org/abs/2203.11601)। TreeLevel Tools द्वारा चलाए जाने वाले अन्य जनक, और उनके
लेखक: [CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/main/CREDITS.md)।

यह TreeLevel से अलग एक प्रोग्राम ही रहता है: ऐप उसे एक कार्य सौंपता है और परिणाम वापस पढ़ता है। ड्राइवर और
`runner.js` का स्रोत कोड इसी रिपॉज़िटरी (`Backends/pythia`) में, टैग `ipad-pythia-module-$MODULE` पर है।
चेकसम `SHA256SUMS.txt` में।
