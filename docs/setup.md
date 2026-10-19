# Set up the tools

The lessons use ESP-IDF v6.0.3, C, and three VS Code extensions. You can do every coding lesson in the Wokwi simulator. A real ESP32-DevKitC is optional and uses the same firmware.

## Extensions

Install these when VS Code prompts, or from the marketplace:

- [ESP-IDF](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/) (`espressif.esp-idf-extension`)
- [Wokwi](https://docs.wokwi.com/vscode/getting-started) (`wokwi.wokwi-vscode`)
- [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) (`llvm-vs-code-extensions.vscode-clangd`)

The repository recommends them in `.vscode/extensions.json`.

## ESP-IDF v6.0.3

1. Command Palette: **ESP-IDF: Open ESP-IDF Installation Manager**. The extension downloads EIM and starts it. On a desktop it opens the EIM window. In SSH, WSL, Dev Containers, or Codespaces it runs `eim wizard` in the terminal. If a download mirror is offered, GitHub is the usual choice. The Espressif download server is the faster choice in China.
2. In EIM, use **Custom** installation and select **v6.0.3**. **Easy Installation** installs the newest stable release, which is newer than the v6.0.3 guides this course links to. Custom installation installs that ESP-IDF tree and its tools (compiler, CMake, Python environment, OpenOCD, and the rest). The same install from a shell, once `eim` is on `PATH`, is `eim install -i v6.0.3`.
3. The extension finds the install by reading `$HOME/.espressif/tools/eim_idf.json` (`C:\Espressif\tools\eim_idf.json` on Windows).
4. Command Palette: **ESP-IDF: Select Current ESP-IDF Version**, and choose the v6.0.3 setup. Then **ESP-IDF: Doctor Command** to confirm the extension, IDF path, and tools.
5. Open a lesson's `firmware` folder as the project. Start with `lessons/01-hello/firmware`. The repository root has no `CMakeLists.txt` on purpose: each lesson is its own project. Command Palette: **ESP-IDF: Pick a Workspace Folder** if the window has more than one folder.
6. **ESP-IDF: Set Espressif Device Target** and choose `esp32`. The chip is the ESP32 on an ESP32-DevKitC V4, which is the board in every `diagram.json`.

From a terminal outside the extension, source the activation script EIM writes:

```bash
. "$HOME/.espressif/tools/activate_idf_v6.0.3.sh"
cd lessons/01-hello/firmware
idf.py set-target esp32
idf.py build
```

The filename matches the installed version. **ESP-IDF: Open ESP-IDF Terminal** is already activated, so you do not source the script there.

`sdkconfig.defaults` already sets `CONFIG_IDF_TARGET="esp32"`. `idf.py set-target esp32` is still the step that creates `sdkconfig` the first time.

### Commands you will use

| In VS Code | In a terminal |
| --- | --- |
| ESP-IDF: Build your Project | `idf.py build` |
| ESP-IDF: Flash your Project | `idf.py -p PORT flash` |
| ESP-IDF: Monitor your Device | `idf.py -p PORT monitor` (quit with Ctrl-]) |
| ESP-IDF: Build, Flash and Monitor | `idf.py -p PORT build flash monitor` |
| ESP-IDF: SDK Configuration Editor | `idf.py menuconfig` |
| ESP-IDF: Full Clean Project | delete the `build` directory |
| ESP-IDF: Select Port to Use | the serial port for a real board |

Wokwi does not replace Build. Build first, then start the simulator. It loads `build/flasher_args.json`, which is the same image set `idf.py flash` would write.

## Wokwi

1. Command Palette: **Wokwi: Request a new License** and activate the free personal license.
2. Build the lesson firmware.
3. Command Palette: **Wokwi: Start Simulator**.

The diagram next to the project shows the DevKitC, and the parts that lesson needs. UART0 is wired to the simulator's serial monitor, 115200 baud.

Wi-Fi lessons join the open network `Wokwi-GUEST` (channel 6, empty password). Do not put a real network password in these projects.

Automated scenarios (`firmware/scenario.yaml`) run with the [Wokwi CLI](https://docs.wokwi.com/wokwi-ci/cli-usage) when `WOKWI_CLI_TOKEN` is set. Without a token, run the same steps by hand in the simulator: press the button, move the slider, read the log.

## clangd

ESP-IDF writes `build/compile_commands.json` when you build or run `idf.py reconfigure`. Each lesson firmware folder contains `.vscode/settings.json` that points clangd at that file and disables the Microsoft C/C++ IntelliSense engine so the two do not fight.

Open the lesson `firmware` folder (or the `host_test` folder) as the workspace so those settings apply. The compiler driver query is `--query-driver=**/*gcc`, which covers `xtensa-esp32-elf-gcc`.

If completion is empty, run **ESP-IDF: Run idf.py reconfigure Task** so `compile_commands.json` exists, then **clangd: Restart language server**.

## Host tests

Lessons with a `logic/` directory have a Unity test in `host_test/`. It builds for the ESP-IDF `linux` target and runs on your computer. From the repository root, after sourcing `activate_idf_v6.0.3.sh` as above:

```bash
./scripts/check-lesson.sh 02
```

That tests your code. It copies the lesson to a temp directory and does not modify your tree. When you want to see the reference pass:

```bash
./scripts/check-lesson.sh 02 --solution
```

The linux target is a preview (`idf.py --preview set-target linux`). It is supported on Linux and macOS. The course CI runs these tests in the `espressif/idf:v6.0.3` image.

## What you do not need

Bluetooth is not simulated by Wokwi on any ESP32, so this course does not use BLE. A later hardware-only exercise can follow the [NimBLE peripheral example](https://github.com/espressif/esp-idf/tree/v6.0.3/examples/bluetooth/nimble/bleprph) on a real board.
