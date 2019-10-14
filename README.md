# War With Gods

War With Gods is a thing we are building. Probably an 2D ARPG.

## Building

Run Cmake:

```
cmake -B build-folder/ .
```

*Note:* If compiling on Window, be sure to specify the CMake generator with `-G ${GENERATOR}`.

## Testing

To build a test variant run the following:

```
cmake -DBUILD_TESTS=ON -B build-folder/ .
```

## Contributing

Make a PR and hope we are merciful.

## License