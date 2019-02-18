import re, sys, argparse

# Objects declaration
# Class definition
# Constructor definition
# Inherited Class definition

def replacer(match):
    s = match.group(0)
    if s.startswith('/'):
        return " "
    elif s.startswith("'"):
        return "''"
    elif s.startswith('"'):
        return '""' 
    else:
        return s
        
def comment_remover(text):
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(\\.|[^\\\'])*\'|"(\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)

def match(kind, args):
    if args.all:
        return True
    if (kind == "O" and args.objects) or (kind == "C" and args.classes) or (kind == "D" and args.constructors) or (kind == "I" and args.inherited_classes):
        return True
    return False

def matchClass(line):
    if re.match(classReg, line):
        classDict.append((re.match("\s*((public|private|protected)\s+)?(static\s+)?class\s+(?P<c>([$_a-zA-Z][$_a-zA-Z0-9]*))(\s+extends\s+[$_a-zA-Z][$_a-zA-Z0-9]*)?(\s+implements\s+[$_a-zA-Z][$_a-zA-Z0-9]*(\s*,\s*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?\s*",line).groupdict()['c']))

class Analyzer():    
    def __init__(self, regex):
        self.regex = regex
        self.count = 0

    def check(self, line, index, kind, args):
        matches = re.findall(self.regex, line)
        if kind is "D" :
            for className in classDict:
                for singleMatch in matches: 
                    if className in singleMatch:
                        if len(matches)>0:
                            if match(kind, args):
                                print(kind + " Line:" + str(index+1)+ " " + line.lstrip())
                            self.count = self.count + 1
                            return
        elif kind is "O":
            if(re.match(objReg, line)):
                if re.match(objReg, line).groupdict()['c'] in classDict:
                    if match(kind, args):
                        print(kind + " Line:" + str(index+1)+ " " + line.lstrip())
                    self.count = self.count + 1
                return                     
                   
        else:
            if len(matches)>0:
                if match(kind, args):
                    print(kind + " Line:" + str(index+1)+ " " + line.lstrip())
                self.count = self.count + 1       

def analyze(args):
    objAnalyzer = Analyzer(objReg)
    classAnalyzer = Analyzer(classReg)    
    constrAnalyzer = Analyzer(constrReg)
    inhClassAnalyzer = Analyzer(inhClassReg)

    filename = args.filename
    f = open(filename, 'r')
    contents = f.read()
    contents = comment_remover(contents)
    with open('input_without_comments.java','w') as input:
        input.write(contents)                

    lines = contents.split("\n")
    for index, line in enumerate(lines):
        matchClass(line)

    for index, line in enumerate(lines):
        objAnalyzer.check(line, index, "O", args)
        classAnalyzer.check(line, index, "C", args) 
        constrAnalyzer.check(line, index, "D", args) 
        inhClassAnalyzer.check(line, index, "I", args)

    print("1) Object Declarations - " + str(objAnalyzer.count))
    print("2) Class Definitions - " + str(classAnalyzer.count))
    print("3) Constructor Definitions - " + str(constrAnalyzer.count))
    print("4) Inherited Class Definitions - " + str(inhClassAnalyzer.count))

str_ = "([$_a-zA-Z][$_a-zA-Z0-9]*)"
objReg = ".*?(\s*(?P<c>([$_a-zA-Z][$_a-zA-Z0-9]*))((\[\])*)(\s*)(<(.*?)>)?(\s*)([$_a-zA-Z][$_a-zA-Z0-9]*)(\s*)(=|,|;))"
classReg = "\s*((public|private|protected)\s+)?(static\s+)?class\s+([$_a-zA-Z][$_a-zA-Z0-9]*)(\s+extends\s+[$_a-zA-Z][$_a-zA-Z0-9]*)?(\s+implements\s+[$_a-zA-Z][$_a-zA-Z0-9]*(\s*,\s*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?\s*"
str_str = "([$_a-zA-Z][$_a-zA-Z0-9]*(\s*((\[\]\s*)|(\s+\[\]))?)\s+[$_a-zA-Z][$_a-zA-Z0-9]*(\s*((\[\]\s*)|(\s+\[\])))?)"
constrReg = "\s*((public|private|protected)\s+)?" + str_ + "\s*" + "\(" + "("+str_str + "(\s*,\s*" + str_str + ")*)*\)\s*([^;]|$)"
inhClassReg = "\s*((public|private|protected)\s+)?class\s+([$_a-zA-Z][$_a-zA-Z0-9]*)(\s+extends\s+[$_a-zA-Z][$_a-zA-Z0-9]*)(\s+implements\s+[$_a-zA-Z][$_a-zA-Z0-9]*(\s*,\s*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?\s*"

classDict=["Double","Byte","Integer","Long","Short","Float","Character","Boolean"]

def main():
    parser = argparse.ArgumentParser(description='Java Analyzer')
    parser.add_argument('-a', '--all', action='store_true', help="Print all declarations")
    parser.add_argument('-o', '--objects', action='store_true', help="Print all occurences of object declarations.")
    parser.add_argument('-c', '--classes', action='store_true', help="Print all occurences of class declarations.")
    parser.add_argument('-d', '--constructors', action='store_true', help="Print all occurences of constructor declarations.")
    parser.add_argument('-i', '--inherited_classes', action='store_true', help="Print all occurences of inherited class declarations.")
    parser.add_argument('-f', '--filename', type=str, default='test.java', help="Input file")
    args = parser.parse_args()
    analyze(args)

if __name__ == '__main__':
    main()

