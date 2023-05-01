import csv
from operator import itemgetter


# Define function for converting keypress, keycode and timesincelastkey into one string
def stringify(keypress, keycode, timesincelastkey):
    string1 = str(keypress) + ':' + str(keycode) + ':' + str(timesincelastkey)
    return string1
"""
Keycodes for example password
l = 76
e = 69
o = 79 
n = 78
a = 65
r = 82
d = 68
o = 79
  = 32
d = 68
i = 73
c = 32
a = 65
p = 80
r = 82
i = 73
o = 79

Keycodes for keys can be found here: https://www.toptal.com/developers/keycode
"""
keycodes = ['76','69','79','78','65','82','68','79','32','68','73','67','65','80','82','73','79']
FileToReadFrom = 'EnterYourInputFile.csv'
FileToReadTo = 'EnterYourOutputFile.csv'

lengthKeycodes = len(keycodes)
lengthDuration = 3+lengthKeycodes
lengthLatency = lengthDuration+lengthKeycodes-1


print('Password is set to:')
for k in range(lengthKeycodes):
  print(chr(int(keycodes[k])),sep='',end='',flush=True)
print('')

# Open the input CSV file for reading
with open(FileToReadFrom, mode='r') as input_file:
  print('Reading from file: ' + FileToReadFrom)
  reader = csv.reader(input_file)
  formatted_data = []
  # Go through every row in the csv file
  for row in reader:
    
    # Extract all duration values and store them in a list
    duration = row[3:lengthDuration]
    # Extract all latency values and store them in a list
    latency = row[lengthDuration:lengthLatency]
    
    # Define keydown and keyup
    keydown = '0'
    keyup = '1'
    # Set timesincelastkey to 0
    timesincelastkey = 0
    
    # Define temporary list for storing keydown/keyup and timesincelastkey
    tempStorage = []

    # Add first entry, will always be 0 for keydown (we have to start with a keypress) and 0 timesincelastkey (because that is when the typing starts)
    tempStorage.append([keydown, timesincelastkey])
    
    # Go through the length of keycodes
    for x in range(lengthKeycodes):
      # This for loop goes through the lists for duration and latency and assigns addsup timesincelastkey and store keyup/keydown in list

      # Add duration to timesincelastkey
      timesincelastkey += int(duration[x])
      # Store in list
      tempStorage.append([keyup, timesincelastkey])
      # This if check is needed because latency is 1 shorter than duration list 
      if x < len(latency):
        timesincelastkey += int(latency[x])
        tempStorage.append([keydown, timesincelastkey])

    # Sort list by timesincelastkey 
    # This fix is needed to compensate for negative latency values, e.g. someone presses the next button before releasing the one before
    tempStorage = sorted(tempStorage, key=itemgetter(1)) # sorting array

    # After sorting, we need to go through every key and get the timesincelastkey value in MS
    # This also fixes negative latency values (because we sorted it first)
    for c in reversed(range(1, len(tempStorage))):
      # We need to start from the back, hence "reversed"
      tempStorage[c][1] -= tempStorage[c-1][1]

    # Set counters to 0
    # Counters are used to grab the correct keycode from keycodes list
    keycodeCounterUp = 0
    keycodeCounterDown = 0

    # Define empty string
    stringy = ''

    # Now go through all values in tempStorage
    for y in range(len(tempStorage)):
      # print(tempStorage[y][0])
      # This for loop creates the correct formatting needed for the c++ program
      # e.g., typeOfKey:keyCode:timeSinceLastKey,typeOfKey:keyCode:timeSinceLastKey,typeOfKey:keyCode:timeSinceLastKey,............
      
      # If keydown
      if tempStorage[y][0] == '0':
        # Convert to correct formatting
        stringy += stringify(tempStorage[y][0],keycodes[keycodeCounterDown],tempStorage[y][1])
        keycodeCounterDown += 1
      else:
      # Else means keyup
        stringy += stringify(tempStorage[y][0],keycodes[keycodeCounterUp],tempStorage[y][1])
        keycodeCounterUp += 1

      # Add ',' if it is no the last value
      if y < len(tempStorage)-1:
        stringy += ','

    # Append values to list
    formatted_row = [row[0], row[1], row[2], stringy]
    formatted_data.append(formatted_row)
        
# Open the output CSV file for writing
with open(FileToReadTo, mode='w', newline='') as output_file:
  print("Writing to file: " + FileToReadTo)
  writer = csv.writer(output_file)
  
  # Write the formatted data to the output CSV file
  writer.writerows(formatted_data)
