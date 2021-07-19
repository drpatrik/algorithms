import os
import audiofile as af


def extract_info(full_path):
    name, extension = os.path.splitext(full_path)

    if extension in ['.flac']:
        return af.bit_depth(full_path), int(af.sampling_rate(full_path) / 1000)
    return 0, 0


def traverse_all_files(dirName):
    listOfFile = os.listdir(dirName)
    for entry in listOfFile:
        full_path = os.path.join(dirName, entry)

        if os.path.isdir(full_path):
            traverse_all_files(full_path)
        else:
            path, filename = os.path.split(full_path)
            if (filename.startswith('.')):
                continue
            bit_depth, sampling_rate = extract_info(full_path)

            if (bit_depth > 16 or sampling_rate > 44):
                print("{} bit_depth: {}, sampling_rate: {}".format(
                      path, bit_depth, sampling_rate))
                break
            elif (bit_depth > 0 and sampling_rate > 0):
                print("WARNING --- {} bit_depth: {}, sampling_rate: {}".format(
                    path, bit_depth, sampling_rate))


def main():
    traverse_all_files('.')


if __name__ == '__main__':
    main()
