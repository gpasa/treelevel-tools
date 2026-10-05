[TreeLevel](https://treelevel.pasahome.org) के घटना जनक, आपके कंप्यूटर पर। TreeLevel एक कार्य को स्थानीय फ़ोल्डर
में लिखता है; यह प्रोग्राम उसे **Pythia 8**, **Herwig 7**, **Sherpa 3**, **WHIZARD 3** या **CalcHEP 3** को सौंपता
है — उसकी घटनाओं का शावर और हैड्रॉनीकरण, या किसी त्वरक की पूरी टक्करें — और परिणाम को HepMC3 में वापस लिखता है,
जिसे TreeLevel पढ़ता है। नेटवर्क पर कुछ नहीं जाता, न कोई खाता, न कोई सेवा। iPad पर WebAssembly में संकलित Pythia 8
यही भूमिका निभाता है, जो [उसकी रिलीज़](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia) से डाउनलोड होता है।

यह अलग से वितरित किया जाता है क्योंकि ये जनक **GPL** लाइसेंस के अंतर्गत हैं: यह रिपॉज़िटरी GPL v3 है, और
TreeLevel में इनका कोई कोड नहीं है।

| सिस्टम | डाउनलोड | इसमें क्या है |
|---|---|---|
| **macOS** 13 या उसके बाद का, Apple Silicon और Intel | [TreeLevelTools-0.5.0.dmg](https://github.com/gpasa/treelevel-tools/releases/download/mac-0.5.0/TreeLevelTools-0.5.0.dmg) | Pythia 8, Herwig 7, Sherpa 3 और CalcHEP 3, चलने के लिए तैयार |
| **Windows** 10 और 11 | [x64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-x64.zip) · [ARM64](https://github.com/gpasa/treelevel-tools/releases/download/win-0.5.1/TreeLevelTools-0.5.1-arm64.zip) | Pythia 8; बाकी Docker इमेज के माध्यम से |
| **iPad** | TreeLevel की सेटिंग्स से ([रिलीज़](https://github.com/gpasa/treelevel-tools/releases/tag/ipad-pythia)) | WebAssembly में Pythia 8 |
| **Docker**, कोई भी सिस्टम | `docker pull ghcr.io/gpasa/treelevel-tools:latest` | पाँचों जनक, WHIZARD 3 सहित |

**Mac**: `TreeLevel Tools.app` को `/Applications` में खींचें और उसे एक बार खोलें; फिर TreeLevel जनन क्षेत्र में
इसके जनक प्रस्तुत करता है। **Windows**: आर्काइव को `%LOCALAPPDATA%\Programs` में निकालें। **iPad**: सेटिंग्स का
*Pythia 8 मॉड्यूल* कार्ड उसे डाउनलोड करता है और हर फ़ाइल जाँचता है। **Docker**: इमेज मौजूद होने पर, TreeLevel Tools
उसमें वे जनक चलाता है जो कोई मॉड्यूल नहीं देता (Mac पर, एक चेकबॉक्स उसे सारे कार्य सौंप देता है)।
