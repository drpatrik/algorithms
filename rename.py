import os


def fix_filename(fullPath, seq_no):
    path, filename = os.path.split(fullPath)
    name, extension = os.path.splitext(filename)

    new_filename = filter(lambda ch: ch.isalnum(), name)
    new_fullpath = os.path.join(path, new_filename) + extension

    if new_fullpath != fullPath and os.path.isfile(new_fullpath):
        new_fullpath = os.path.join(
            path, new_filename + str(seq_no)) + extension
        seq_no = seq_no + 1

    return seq_no, new_fullpath


def rename_all_files(dirName):
    seq_no = 0
    listOfFile = os.listdir(dirName)
    for entry in listOfFile:
        fullPath = os.path.join(dirName, entry)

        if os.path.isdir(fullPath):
            rename_all_files(fullPath)
        else:
            seq_no, new_fullpath = fix_filename(fullPath, seq_no)

            if (new_fullpath != fullPath):
                print("Rename: " + fullPath + " to " + new_fullpath)
                os.rename(fullPath, new_fullpath)
            else:
                print("Ignored: " + fullPath)


def main():
    rename_all_files('.')


if __name__ == '__main__':
    main()
