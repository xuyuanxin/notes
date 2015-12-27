from optparse import OptionParser  

'''
<yourscript> --file=outfile -q  
<yourscript> -f outfile --quiet  
<yourscript> --quiet --file outfile  
<yourscript> -q -foutfile  
<yourscript> -qfoutfile  
'''

def main():
    usage = "usage: %prog [options] arg"
    parser = OptionParser(usage)
    parser.add_option("-f", "--file", dest="filename",
                      help="read data from FILENAME")
    parser.add_option("-v", "--verbose",
                      action="store_true", dest="verbose")
    parser.add_option("-q", "--quiet",
                      action="store_false", dest="verbose")

    (options, args) = parser.parse_args()

    print('(options, args):%s %s'%(options,args))

    if len(args) != 1:
        #parser.error("incorrect number of arguments")
        pass

    if options.verbose:
        print "reading %s..." % options.filename
	
    print('-------')

if __name__ == "__main__":
    main()
	
	
	
'''
parser = OptionParser()  
parser.add_option("-f", "--file", dest="filename",  
                  help="write report to FILE", metavar="FILE") 

parser.add_option('--alexa-file', default='data/alexa_100k.csv', help='Alexa file to pull from.  Default: %default')				  

parser.add_option("-q", "--quiet",  
                  action="store_false", dest="verbose", default=True,  
                  help="don't print status messages to stdout")  
  
(options, args) = parser.parse_args()

print options, args
options.alexa_file
'''