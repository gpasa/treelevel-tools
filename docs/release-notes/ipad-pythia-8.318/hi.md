WebAssembly में संकलित Pythia 8, TreeLevel Tools के साझा ड्राइवर के साथ। iPad पर TreeLevel इसे इस पृष्ठ से,
फ़ाइल-दर-फ़ाइल, डाउनलोड करता है, और हर फ़ाइल को ऐप में स्थिर एक फ़िंगरप्रिंट से जाँचता है; वह इसे एक वेब व्यू में
चलाता है, कहीं कुछ भी भेजे बिना। घटनाएँ इससे शावर और हैड्रॉनीकरण के साथ निकलती हैं, और TreeLevel का त्वरक स्रोत
iPad पर उपलब्ध हो जाता है।

| फ़ाइल | भूमिका |
|---|---|
| `treelevel-pythia-web.wasm`, `.js` | Pythia 8.318 और ड्राइवर, WebAssembly में |
| `runner.js` | TreeLevel का एक कार्य चलाता है: योजना, भाग, विलय |
| `leptons.pack` | Pythia के आँकड़े (xmldoc, tunes, setups) — लेप्टॉन किरणपुंज |
| `pdfdata.pack` | पार्टन घनत्व — हैड्रॉन किरणपुंज, वैकल्पिक |
| `pythia8318-sources.tgz` | Pythia 8.318 का स्रोत कोड, जैसा वह pythia.org पर प्रकाशित है |
| `COPYING.pythia8` | Pythia का लाइसेंस (GPL v2 या उसके बाद का) |

### Pythia 8, उसके लेखक

Pythia 8 © Torbjörn Sjöstrand और Pythia सहयोग-समूह — [pythia.org](https://pythia.org) — है, और GPL v2 या उसके
बाद के संस्करण के अंतर्गत वितरित होता है। इस मॉड्यूल की सारी भौतिकी उन्हीं की है। यदि आप इसके साथ प्राप्त कोई परिणाम
प्रकाशित करें, तो उद्धृत करें: C. Bierlich et al., “A comprehensive guide to the physics and usage of PYTHIA 8.3”,
*SciPost Phys. Codebases* 8 (2022), [arXiv:2203.11601](https://arxiv.org/abs/2203.11601)।

TreeLevel Tools द्वारा चलाए जाने वाले अन्य जनक, और उनके लेखक:
[CREDITS.md](https://github.com/gpasa/treelevel-tools/blob/1.3-dev/CREDITS.md)।
यह TreeLevel से अलग एक प्रोग्राम ही रहता है: ऐप उसे एक कार्य सौंपता है और परिणाम वापस पढ़ता है। ड्राइवर और
`runner.js` का स्रोत कोड इसी रिपॉज़िटरी में, इस रिलीज़ के टैग पर है (`Backends/pythia`)।
चेकसम `SHA256SUMS.txt` में।
