# firew0rks

Play text art animations in your terminal! This package includes several pre-made animations like fireworks and a cozy fireplace.

![Eowzf_jWMAAk43x](https://github.com/user-attachments/assets/58d4c0ef-9f0b-49ae-80f0-4e12db3e34f0)

## Compile the program

```bash
gcc -o firew0rks main.c
```

## Usage

```bash
./firew0rks [folder] [loops]
```

Parameters (all optional):
- `[folder]`: Folder containing text art frames (numbered 0.txt, 1.txt, etc.). Defaults to 'fireworks'
- `[loops]`: Number of times to loop the animation (-1 for infinite)

## Examples
Play the fireworks animation with custom loops:
```bash
./firew0rks fireworks 3
```

Enjoy a cozy fireplace forever:
```bash
./firew0rks fireplace 3
```

## Creating Your Own Animations

1. Create a new folder for your animation
2. Add text art frames as numbered .txt files (0.txt, 1.txt, 2.txt, etc.)
3. Run firew0rks with your folder name

## Acknowledgments

This project is a C port of [firew0rks](https://github.com/addyosmani/firew0rks) by addyosmani. Thank you for the inspiration and the amazing ASCII art animations!

## License

MIT
