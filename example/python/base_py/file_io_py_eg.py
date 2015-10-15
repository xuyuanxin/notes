'''
Listing 11-8. Using readline in a while Loop
f = open(filename)
while True:
    line = f.readline()
    if not line: break
    process(line)
f.close()

Listing 11-9. Iterating over Characters with read
f = open(filename)
for char in f.read():
    process(char)
f.close()

Listing 11-10. Iterating over Lines with readlines
f = open(filename)
for line in f.readlines():
    process(line)
f.close()
'''