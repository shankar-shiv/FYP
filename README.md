## Guiding questions
1. What are the options for creating a user interface?
There seems to be already a well documented Electron desktop application, see [this](https://nordicsemiconductor.github.io/pc-ble-driver-js/) and [this](https://github.com/NordicSemiconductor/pc-ble-driver-py) with lots of examples in which we can adapt for your use cases.

2. What factors should we consider?
We need more libraries support for the particular platform in which we are going to choose.

3. What is the platform we are aiming for (Desktop, Mobile application or Web)?

4. Is there software support for the respective platform, Android iOS Flutter React Native

| **Mobile application**    | pros                               | cons                                                                 | BLE library                                                                                                                                                    | Github ⭐⬆️ |
| ------------------------- | ---------------------------------- | -------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------- |
| Android                   | the best if possible               | Kotlin or Java (only Java is used for Azure functions)               | Native BLE or [Kotlin-BLE-Library](https://github.com/NordicSemiconductor/Kotlin-BLE-Library)                                                                  | inf       |
| iOS                       | Uses Swift                         | but incompatible with Azure                                          | Native or [IOS-BLE-Library](https://github.com/NordicSemiconductor/IOS-BLE-Library)                                                                            | inf       |
| Kivy (Python)             | its all in python                  | not really sure how it will turn out with regards to using bluetooth | [Android-BLE-Library](https://github.com/NordicSemiconductor/Android-BLE-Library)                                                                              | 16.3k     |
| React Native (Typescript) | very wide range of library support | not really confident and the devx seems to be tiring :x              | [React Native BLE PLX](https://github.com/dotintent/react-native-ble-plx) and [react-native-ble-manager](https://github.com/innoveit/react-native-ble-manager) | 112k      |

| [Ranking] **Desktop application**                  | pros                                                          | cons                                                                                                  | BLE Library                                                                                                                             | Github ⭐⬆️ |
| -------------------------------------------------- | ------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------- | --------- |
| [Textual](https://textual.textualize.io/) (Python) | its fast, runs in terminal                                    | Does not have built-in support for images and does not really plot data (have to use another library) | [pc-ble-driver-py](https://github.com/NordicSemiconductor/pc-ble-driver-py)                                                             | 21.6k     |
| 5. NiceGUI (Python)                                | good for robotics like standalone(Python)                     | very new has the least amount of stars, among all frameworks                                          | [pc-ble-driver-py](https://github.com/NordicSemiconductor/pc-ble-driver-py)                                                             | 5.5k      |
| 3. Reflex (Python)                                 | can jump into react if required (Python)                      | As of July 2023, we are in the Public Beta stage.                                                     | [pc-ble-driver-py](https://github.com/NordicSemiconductor/pc-ble-driver-py)                                                             | 13.1k     |
| 1. Dash (Python)                                   | very popular (Python)                                         | ⚠️                                                                                                     | [pc-ble-driver-py](https://github.com/NordicSemiconductor/pc-ble-driver-py)                                                             | 19.4k     |
| 4. Electron (Typescript)                           | has the most support from the Nordin team for JS (Typescript) | ⚠️                                                                                                     | [pc-ble-driver-js](https://nordicsemiconductor.github.io/pc-ble-driver-js/) and https://github.com/NordicSemiconductor/pc-ble-driver-js | 109k      |
| 2. Kivy (Python)                                   | is very versatile (Python)                                    | ⚠️                                                                                                     | [pc-ble-driver-py](https://github.com/NordicSemiconductor/pc-ble-driver-py)                                                             | 16.3k     |
| NA. customtkinter (Python)                         | an advanced version of tkinter(Python)                        | this library is under active development😱                                                             | [pc-ble-driver-py](https://github.com/NordicSemiconductor/pc-ble-driver-py)                                                             | 8.6k      |

I will be testing Dash, Kivy, Reflex, React Native (both in expo and electron js) and NiceGUI.

## Discussion on NiceGUI, Reflex
- https://www.reddit.com/r/Python/comments/16p4rgd/tkinter_gradio_and_dearpygui/
- https://www.reddit.com/r/Python/comments/16t8r3p/can_we_create_production_ready_applications_with/
- This link also explain the problems with streamlit's state management model. https://github.com/zauberzeug/nicegui/issues/1

### References
- [nRF Connect for Desktop](https://nordicsemiconductor.github.io/pc-nrfconnect-docs/)