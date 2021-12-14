import re
import string

# Function to list all items and their purchasing frequencies.
def ListAllFrequencies():
    # Open file using 'with' to ensure file gets closed.
    with open('FileInput.txt', 'r') as read_file:
        # Create a first list of strings containing each line of the file.
        prelim_list = read_file.readlines()
    
        # Create a second, empty list.
        all_items = []
        # Loop over first list and remove newlines from all words, store stripped word into second list.
        for item in prelim_list:
            all_items.append(item.strip())

        # Create an empty dictionary.
        items_dict = {}
        # Loop over stripped list.
        for item in all_items:
            if item in items_dict:
                # If item is in dictionary, increase count.
                items_dict[item] = items_dict[item] + 1
            else:
                # If item is not in dictionary, add and assign 1 as first count.
                items_dict[item] = 1

        # Loop over pairs in dictionary.
        for item, frequency in items_dict.items():
            # Print each item and its coresponding number, or count.
            print('{}: {}'.format(item, frequency))

def ListSpecificFrequency(v):
    # Open file using 'with' to ensure file gets closed.
    with open('FileInput.txt', 'r') as read_file:
        # Create a first list of strings containing each line of the file.
        prelim_list = read_file.readlines()
    
        # Create a second, empty list.
        all_items = []
        # Loop over first list and remove newlines from all words, store stripped word into second list.
        for item in prelim_list:
            all_items.append(item.strip())

        frequency = all_items.count(v)

        return frequency

def CreateFrequencyFile():
    with open('FileInput.txt', 'r') as read_file:
        # Create a first list of strings containing each line of the file.
        prelim_list = read_file.readlines()
    
        # Create a second, empty list.
        all_items = []
        # Loop over first list and remove newlines from all words, store stripped word into second list.
        for item in prelim_list:
            all_items.append(item.strip())

        # Create an empty dictionary.
        items_dict = {}
        # Loop over stripped list.
        for item in all_items:
            if item in items_dict:
                # If item is in dictionary, increase count.
                items_dict[item] = items_dict[item] + 1
            else:
                # If item is not in dictionary, add and assign 1 as first count.
                items_dict[item] = 1

    with open('frequency.dat', 'w') as write_file:
        # Variable to keep track of place in dictionary, used to avoid printing newline after last entry
        i = 1
        for item, frequency in items_dict.items():
            # Print each item and its coresponding number, or count.
            write_file.write('{} {}'.format(item, frequency))
            # If not the last item in the dictionary, print a newline
            if i < len(items_dict):
                write_file.write('\n')
            i += 1