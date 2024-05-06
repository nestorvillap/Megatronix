# Cache Simulation Program

This is a cache simulation program that demonstrates how a simplified Linux-like cache system works with the following configurations:

- **Address Size**: 12 bits
- **Line Size**: 3 bits
- **Tag Size**: 5 bits
- **Word Size**: 4 bits

## Memory and Cache

- **RAM**: 256 blocks, 4096 bytes total
- **Cache**:
  - Size: 128 bytes
  - Lines: 8
  - Line Size: 16 bytes

## Key Functions

- **`TratarFallo`**: Handles cache misses, updating tags and data from the RAM.
- **`leerLinea`**: Reads a specific line from an input file.
- **`LimpiarCACHE`**: Initializes the cache with default values.
- **`VolcarCACHE`**: Prints the current state of the cache.
- **`guardarCache`**: Saves the cache content to a binary file.
- **`ParsearDireccion`**: Parses an address to obtain tag, line, and word values.
