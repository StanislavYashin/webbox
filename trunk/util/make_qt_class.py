import os

def qt_class(ClassName, BaseName):
    classdef = '''\nclass %s : public %s
{\n
Q_OBJECT\n
/*METHODS*/
public:
\n
protected:
\n
private:
\n
/*FIELDS*/ 
public:
\n
protected:
\n
private:
\n
};'''%(ClassName,BaseName)
                
    return classdef
    
if __name__ == "__main__":
    class_name = input("class name:")
    base_name = input("base name:")
    print(qt_class(class_name,base_name)) 
