
all: Hello.class

SRCS=$(wildcard Hello*.java)
OBJS=${SRCS:.java=.class}
CLASS_NAMES=${SRCS:.java=}

%.class: %.java
	javac -classpath ../target/rocksdbjni-6.14.6-linux64.jar $<

# Hello.class:Hello.java
# 	javac -classpath ../target/rocksdbjni-6.14.6-linux64.jar Hello.java

run:
	for CN in ${CLASS_NAMES} ; do \
		echo " ====== Running: " $${CN} "=========" ; \
		java -cp ../target/rocksdbjni-6.14.6-linux64.jar:. $${CN} ; \
	done

clean:
	rm -f *.class

