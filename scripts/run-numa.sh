#!/bin/bash
scriptDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
mainDir="${scriptDir}/.."
evalDir="${scriptDir}/../eval"
tcmalloc="env LD_PRELOAD=${HOME}/gperftools/.libs/libtcmalloc.so "

#/!\ This script will NOT work if you modify main.c

#
#Run YCSB A B C (D = A, F =B)
#4 workers per disk, 4 load injectors
#
rm -f ${mainDir}/eval/*

for li_ratio in {1..9};
do
	rm -f /pmem*/kvell_zzunny/* # reset DB

	cp ${mainDir}/main.c ${mainDir}/main.c.bak
	#cat ${mainDir}/main.c | perl -pe 's://.nb_load_injectors = 8:.nb_load_injectors = 8:' | perl -pe 's:[^/].nb_load_injectors = 16: //.nb_load_injectors = 16:' | perl -pe 's:[^/]ycsb_e_uniform,: //ycsb_e_uniform,:' | perl -pe 's://ycsb_a_uniform,:ycsb_a_uniform,:' | perl -pe 's://ycsb_a_zipfian,:ycsb_a_zipfian,:' > ${mainDir}/main.c.tmp
	cat ${mainDir}/main.c  | perl -pe 's:[^/]ycsb_e_uniform,: //ycsb_e_uniform,:' | perl -pe 's://ycsb_a_uniform,:ycsb_a_uniform,:' | perl -pe 's://ycsb_a_zipfian,:ycsb_a_zipfian,:' > ${mainDir}/main.c.tmp
	mv ${mainDir}/main.c.tmp ${mainDir}/main.c
	make -C ${mainDir} -j
	
	worker_ratio=$((10-$li_ratio))
	echo "Run 1"
	${tcmalloc} ${mainDir}/main 4 $li_ratio $worker_ratio | tee $evalDir/log_ycsb_Key8byte_Value8byte_FullThread_DRAM30GB_${li_ratio}:${worker_ratio}_1

	#echo "Run 2"
	#${tcmalloc} ${mainDir}/main 4 $thread_per_pmem | tee $evalDir/log_ycsb_T${thread_per_pmem}_LI8_2

	mv ${mainDir}/main.c.bak ${mainDir}/main.c
done

#
#Run YCSB E
#3 workers per disk, 12 load innjectors
#
for li_ratio in {1..9};
do
	rm -f /pmem*/kvell_zzunny/* # reset DB

	cp ${mainDir}/main.c ${mainDir}/main.c.bak
	#cat ${mainDir}/main.c | perl -pe 's://.nb_load_injectors = 16:.nb_load_injectors = 16:' | perl -pe 's:[^/].nb_load_injectors = 8: //.nb_load_injectors = 8:' | perl -pe 's://ycsb_e_uniform, y:ycsb_e_uniform, y:' | perl -pe 's:[^/]ycsb_a_uniform,: //ycsb_a_uniform,:' | perl -pe 's:[^/]ycsb_a_zipfian,: //ycsb_a_zipfian,:' > ${mainDir}/main.c.tmp
	cat ${mainDir}/main.c  | perl -pe 's://ycsb_e_uniform, y:ycsb_e_uniform, y:' | perl -pe 's:[^/]ycsb_a_uniform,: //ycsb_a_uniform,:' | perl -pe 's:[^/]ycsb_a_zipfian,: //ycsb_a_zipfian,:' > ${mainDir}/main.c.tmp
	cp ${mainDir}/main.c.tmp ${mainDir}/main.c
	make -C ${mainDir} -j

	worker_ratio=$((10-$li_ratio))
	echo "Run 1 (scans)"
	${tcmalloc} ${mainDir}/main 4 $li_ratio $worker_ratio | tee $evalDir/log_ycsb_e_Key8byte_Value8byte_FullThread_DRAM30GB_${li_ratio}:${worker_ratio}_1

	#echo "Run 2 (scans)"
	#${tcmalloc} ${mainDir}/main 4 $thread_per_pmem | tee $evalDir/log_ycsb_e_T${thread_per_pmem}_LI8_2

	mv ${mainDir}/main.c.bak ${mainDir}/main.c
done

#
#Show results
#
#${scriptDir}/parse.pl log_ycsb_*
cp ${mainDir}/eval/* ${mainDir}/eval_persist
