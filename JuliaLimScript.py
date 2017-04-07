## Julia Lim
## Applied Pathways Assignment Script

#print "opening"
text_file = open("appliedpathways_input_file.txt","r")


from prettytable import *
x = PrettyTable()


x.field_names = ["Question Label", "Answer Values", "Type"]


class DataSet:
    node_id = "0000"
    name = "noname"
    basetext = "none"
    type = "none"
    answer_names = "none"

count = DataSet()

## this basically skips the first 7 lines which I considered the introduction
for line in text_file:
    introduction = line
    if "#--------------------" in line:
        #print "introduction found"
        break

## reads file line by line
for line in text_file:

        if "node_id" in line:
            count.node_id = line
            
        if ("name" in line) and ("answer" not in line):
            n = line.index(':')
            line = line[(n+1):] #skips past the labels to get necessary info
            count.name = line
            
        if ("type" in line) and ("sub" not in line):
            n = line.index(':')
            line = line[(n+1):]
            count.type = line
            
            if ("recommendations" in count.type) or ("messages" in count.type): #(("recommendations" in line) or ("messages" in line)):
                count.answer_names = ''
            else:
                count.answer_names = '' # creates blank slate for count.answer_name 

        if "stop" in line:
            count.name = " stop"
            count.type = " stop"
            x.add_row([count.name , count.answer_names, count.type])
                
        if ("answer_names" in line) and ("question" in count.type):
            n = line.index(':')
            line = line[(n+1):]
            count.answer_names = line
            
        if "expression" in count.type and ("additionaldata" and "value" in line):
            n = line.index(': ')# the extra space is because there's two instances of ':' but the second has a space after it
            line = line[(n+1):] 
            count.answer_names = line

        if "#--------------------" in line:
            x.add_row([count.name , count.answer_names, count.type])
            # new row for every set of data

x.align = "l"
print x
