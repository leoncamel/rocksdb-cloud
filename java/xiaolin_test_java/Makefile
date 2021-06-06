
all: Hello.class

SRCS=$(wildcard Hello*.java)
OBJS=${SRCS:.java=.class}
CLASS_NAMES=${SRCS:.java=}

JAVA_OPTS=-Xms1g -Xmx1g -verbose:gc -XX:+UseConcMarkSweepGC -XX:+UseParNewGC \
-XX:OnOutOfMemoryError="kill -9 %p" -XX:+HeapDumpOnOutOfMemoryError \
-XX:HeapDumpPath="./memleaktest.hprof"

%.class: %.java
	javac -classpath ../target/rocksdbjni-6.14.6-linux64.jar $<

# Hello.class:Hello.java
# 	javac -classpath ../target/rocksdbjni-6.14.6-linux64.jar Hello.java

run: ${OBJS}
	for CN in ${CLASS_NAMES} ; do \
		echo " ====== Running: " $${CN} "=========" ; \
		java ${JAVA_OPTS} -cp ../target/rocksdbjni-6.14.6-linux64.jar:. $${CN} ; \
	done

dbg:
	gdb --args ${JAVA_HOME}/bin/java -cp ../target/rocksdbjni-6.14.6-linux64.jar:. Hello

dump-heap:
	echo "jmap -dump:live,format=b,file=heap.hprof <pid>"
	echo "jhat ./heap.hprof"

clean:
	rm -f *.class aws_sdk*.log hs_err*.log

clean-minio:
	mc rm --recursive --force myminio/rocksetcloud.durable.example/.rockset/
	mc rm --recursive --force myminio/rocksetcloud.durable.example/objpath/
	mc rb myminio/rocksetcloud.durable.example/
