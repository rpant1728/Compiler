import re, sys

# Objects declaration
# Class definition
# Constructor definition
# Inherited Class definition

def replacer(match):
    s = match.group(0)
    if s.startswith('/'):
        return " " 
    else:
        return s
        
def comment_remover(text):
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

class Analyzer():    
    def __init__(self, regex):
        self.regex = regex
        self.count = 0

    # def check(self, contents):
    #     matches = re.findall(self.regex, contents)
    #     print(matches)
    #     # for match in matches:
    #     #     print(match+"\n")
    #     self.count = self.count + len(matches)
    def check(self, line):
        if re.match(self.regex, line):
            self.count = self.count + 1
            print(line)

def analyze():
    objAnalyzer = Analyzer(objReg)
    classAnalyzer = Analyzer(classReg)    
    constrAnalyzer = Analyzer(constrReg)
    inhClassAnalyzer = Analyzer(inhClassReg)

    filename = sys.argv[1]
    f = open(filename, 'r')
    contents = f.read()
    contents = comment_remover(contents)
    lines = contents.split("\n")
    for line in lines:
        objAnalyzer.check(line)
        classAnalyzer.check(line) 
        constrAnalyzer.check(line) 
        inhClassAnalyzer.check(line)
    # objAnalyzer.check(contents)
    # classAnalyzer.check(contents) 
    # constrAnalyzer.check(contents) 
    # inhClassAnalyzer.check(contents)

    print("1) Object Declarations - " + str(objAnalyzer.count))
    print("2) Class Definitions - " + str(classAnalyzer.count))
    print("3) Constructor Definitions - " + str(constrAnalyzer.count))
    print("4) Inherited Class Definitions - " + str(inhClassAnalyzer.count))

objReg = "\s*([$_a-zA-Z][$_a-zA-Z0-9]*)((\[\])*)(\s*)(<(\s*)([$_a-zA-Z][$_a-zA-Z0-9]*)(\s*),(\s*)([$_a-zA-Z][$_a-zA-Z0-9]*)(\s*)>)?(\s*)([$_a-zA-Z][$_a-zA-Z0-9]*)(\s*)=(\s*)new(\s+)([$_a-zA-Z][$_a-zA-Z0-9]*)\s*((\()|(\[))"
classReg = "\s*((public|private|protected)\s+)?class\s+([$_a-zA-Z][$_a-zA-Z0-9]*)\s+(extends\s+[$_a-zA-Z][$_a-zA-Z0-9]*\s+)?(implements\s+[$_a-zA-Z][$_a-zA-Z0-9]*(\s*,\s*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?\s*"
str_str = "([$_a-zA-Z][$_a-zA-Z0-9]*\s+[$_a-zA-Z][$_a-zA-Z0-9]*)"
str_ = "([$_a-zA-Z][$_a-zA-Z0-9]*)"
constrReg = "\s*((public|private|protected)\s+)?" + str_ + "\s*" + "\(" + "("+str_str + "(\s*,\s*" + str_str + ")*)*\)\s*"
inhClassReg = "\s*((public|private|protected)\s+)?class\s+([$_a-zA-Z][$_a-zA-Z0-9]*)\s+(extends\s+[$_a-zA-Z][$_a-zA-Z0-9]*\s+)(implements\s+[$_a-zA-Z][$_a-zA-Z0-9]*(\s*,\s*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?\s*"

def main():
    analyze()

if __name__ == '__main__':
    print(constrReg)
    main()


# \s*((public|private|protected)\s+)?([$_a-zA-Z][$_a-zA-Z0-9]*)\s*\((([$_a-zA-Z][$_a-zA-Z0-9]*\s+[$_a-zA-Z][$_a-zA-Z0-9]*)(\s*,\s*([$_a-zA-Z][$_a-zA-Z0-9]*\s+[$_a-zA-Z][$_a-zA-Z0-9]*))*)*\)\s*