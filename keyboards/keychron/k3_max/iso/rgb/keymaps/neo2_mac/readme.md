# Neo2 macOS keymap (K3 Max ISO RGB)

Firmware-side Neo2 for macOS **without Karabiner** (layers 1–4 only).

## How it works

| Layer | Mechanism |
|-------|-----------|
| 1–2 | macOS input source **Deutsch (Neo 2)** + `NE_*` key positions |
| 3 | Hold Caps or `#` (`MO(NEO_3)`) → firmware holds **Right Option** while you type |
| 4 | Hold `<>` or right Cmd position (`MO(NEO_4)`) → firmware holds **Right Command** while you type |

## macOS setup

1. Install [jgosmann/neo2-layout-osx](https://github.com/jgosmann/neo2-layout-osx) (recommended) or Apple Neo2.
2. Select **Deutsch (Neo 2)** as input source.
3. **System Settings → Keyboard → Caps Lock → No Action**

## Build / flash

```bash
make keychron/k3_max/iso/rgb:neo2_mac
make keychron/k3_max/iso/rgb:neo2_mac:flash
```

Reset: mode switch to Cable, hold **Esc** (or reset under spacebar) while plugging in USB.

## Key changes vs stock Keychron

- **Fn** stays on the **bottom row** (stock position, hold for Fn layer).
- **Mod3**: Caps + `#` (ISO key left of Enter).
- **Mod4**: `<>` (left of Z) + key left of Fn (stock Right Cmd position; no Right Cmd sent).
- VIA disabled for this keymap (flash `keychron` again to use VIA).

## Quick test

1. Type `x` `ü` `ß` (layer 1).
2. Hold Caps, press Neo-`s` (QWERTY `i` key) → expect `/` (layer 3).
3. Hold Mod4 (<> key), press keys under left hand → arrows / navigation (layer 4).
