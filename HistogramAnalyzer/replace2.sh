#!/bin/bash
#Histogram names and ranges to be replaced get declared here. arr is for the particle gated and arr2 is for the gamma gated
declare -a arr=("Ex_40_48" "Ex_41_49" "Ex_42_50" "Ex_43_51" "Ex_44_52" "Ex_45_53" "Ex_46_54" "Ex_47_55" "Ex_48_56" "Ex_49_57" "Ex_50_58" "Ex_51_59" "Ex_52_60" "Ex_53_61" "Ex_54_62" "Ex_55_63" "Ex_56_64" "Ex_57_65" "Ex_58_66" "Ex_59_67" "Ex_60_68" "Ex_61_69" "Ex_62_70")
declare -a arr2=("Ex_40_50" "Ex_41_51" "Ex_42_52" "Ex_43_53" "Ex_44_54" "Ex_45_55" "Ex_46_56" "Ex_47_57" "Ex_48_58" "Ex_49_59" "Ex_50_60" "Ex_51_61" "Ex_52_62" "Ex_53_63" "Ex_54_64" "Ex_55_65" "Ex_56_66" "Ex_57_67" "Ex_58_68" "Ex_59_69" "Ex_60_70")
let l=40
let h=48
let ol=40
let oh=48

#first for loop goes through the particle only gated gamma histograms.
for ((i=0; i<${#arr[*]}; i++));
do

	root -l -q .x HistogramAnalyzer2.cxx

	let l=l+1
	let h=h+1
	
	sed -i "22s/${arr[i]}/${arr[i+1]}/" HistogramAnalyzer2.cxx
	sed -i "24s/${arr[i]}/${arr[i+1]}/" HistogramAnalyzer2.cxx
	sed -i "12s/$ol/$l/" HistogramAnalyzer2.cxx
	sed -i "13s/$oh/$h/" HistogramAnalyzer2.cxx

	let ol=ol+1
	let oh=oh+1

done

#change values back to initial
sed -i "22s/${arr[22]}/${arr[0]}/" HistogramAnalyzer2.cxx
sed -i "24s/${arr[22]}/${arr[0]}/" HistogramAnalyzer2.cxx
sed -i "12s/62/40/" HistogramAnalyzer2.cxx
sed -i "13s/70/48/" HistogramAnalyzer2.cxx

let l=40
let h=50
let ol=40
let oh=50

SingleGams=(238 275 1233 1297 1340 2556 1840)
DoubleGams=(2381297 2382556 2384362 2381840 2384140 2751233 2751340 2752632 25561840)

linenums=(20 23 26 31 32 33 36 37)

#second for loop goes through the Gamma gated histograms
for ((d=0; d<2; d++));
do
	for ((g=0; g<${#SingleGams[*]}; g++));
	do

		for ((i=0; i<${#arr2[*]}; i++));
		do

			root -l -q .x HistogramAnalyzer4.cxx

			let l=l+1
			let h=h+1

			sed -i "22s/${arr2[i]}/${arr2[i+1]}/" HistogramAnalyzer4.cxx
			sed -i "24s/${arr2[i]}/${arr2[i+1]}/" HistogramAnalyzer4.cxx
			sed -i "12s/$ol/$l/" HistogramAnalyzer4.cxx
			sed -i "13s/$oh/$h/" HistogramAnalyzer4.cxx
	
			let ol=ol+1
			let oh=oh+1

		done
		if [ g -lt ${#SingleGams[*]}-1 ]
		then
			#change histogram names
			sed -i "22s/Gam${SingleGams[g]}/Gam${SingleGams[g+1]}/" HistogramAnalyzer4.cxx
			sed -i "24s/Gam${SingleGams[g]}/Gam${SingleGams[g+1]}/" HistogramAnalyzer4.cxx
			#Change storage folder
			sed -i "26s/Gam${SingleGams[g]}/Gam${SingleGams[g+1]}/" HistogramAnalyzer4.cxx
			sed -i "201s/Gam${SingleGams[g]}/Gam${SingleGams[g+1]}/" HistogramAnalyzer4.cxx
			#change back the low and high numbers
			sed -i "12s/$l/40/" HistogramAnalyzer4.cxx
			sed -i "13s/$h/50/" HistogramAnalyzer4.cxx

			let l=40
			let h=50
			let ol=40
			let oh=50
		fi
	
	done

	#change the detector name here for the second pass
	if [ d -lt 1 ]
	then
		for ((l=0; l<${#linenums[*]}; l++));
		do
			sed -i "${linenums[l]}s/Si_/QQQ_" HistogramAnalyzer4.cxx
		done
		
	fi

done

#change values back to initial!
for ((l=0; l<${#linenums[*]}; l++));
do
	sed -i "${linenums[l]}s/QQQ_/Si_" HistogramAnalyzer4.cxx
done
sed -i "22s/${arr2[20]}/${arr2[0]}/" HistogramAnalyzer4.cxx
sed -i "24s/${arr2[20]}/${arr2[0]}/" HistogramAnalyzer4.cxx
sed -i "12s/60/40/" HistogramAnalyzer4.cxx
sed -i "13s/70/50/" HistogramAnalyzer4.cxx
#change back histogram names
sed -i "22s/Gam${SingleGams[6]}/Gam${SingleGams[0]}/" HistogramAnalyzer4.cxx
sed -i "24s/Gam${SingleGams[6]}/Gam${SingleGams[0]}/" HistogramAnalyzer4.cxx
#Change back storage folder
sed -i "26s/Gam${SingleGams[6]}/Gam${SingleGams[0]}/" HistogramAnalyzer4.cxx
sed -i "201s/Gam${SingleGams[6]}/Gam${SingleGams[0]}/" HistogramAnalyzer4.cxx

let l=40
let h=50
let ol=40
let oh=50

#third for loop goes through the double Gamma gated histograms
for ((d=0; d<2; d++));
do
	for ((g=0; g<${#DoubleGams[*]}; g++));
	do

		for ((i=0; i<${#arr2[*]}; i++));
		do

			root -l -q .x HistogramAnalyzer5.cxx

			let l=l+1
			let h=h+1

			sed -i "22s/${arr2[i]}/${arr2[i+1]}/" HistogramAnalyzer5.cxx
			sed -i "24s/${arr2[i]}/${arr2[i+1]}/" HistogramAnalyzer5.cxx
			sed -i "12s/$ol/$l/" HistogramAnalyzer5.cxx
			sed -i "13s/$oh/$h/" HistogramAnalyzer5.cxx
	
			let ol=ol+1
			let oh=oh+1

		done
		if [ g -lt ${#SingleGams[*]}-1 ]
		then
			#change histogram names
			sed -i "22s/Gam${DoubleGams[g]}/Gam${DoubleGams[g+1]}/" HistogramAnalyzer5.cxx
			sed -i "24s/Gam${DoubleGams[g]}/Gam${DoubleGams[g+1]}/" HistogramAnalyzer5.cxx
			#Change storage folder
			sed -i "26s/Gam${DoubleGams[g]}/Gam${DoubleGams[g+1]}/" HistogramAnalyzer5.cxx
			sed -i "201s/Gam${DoubleGams[g]}/Gam${DoubleGams[g+1]}/" HistogramAnalyzer5.cxx
			#change back the low and high numbers
			sed -i "12s/$l/40/" HistogramAnalyzer5.cxx
			sed -i "13s/$h/50/" HistogramAnalyzer5.cxx

			let l=40
			let h=50
			let ol=40
			let oh=50
		fi
	
	done

	#change the detector name here for the second pass
	if [ d -lt 1 ]
	then
		for ((l=0; l<${#linenums[*]}; l++));
		do
			sed -i "${linenums[l]}s/Si_/QQQ_" HistogramAnalyzer5.cxx
		done
		
	fi

done

#change values back to initial!
for ((l=0; l<${#linenums[*]}; l++));
do
	sed -i "${linenums[l]}s/QQQ_/Si_" HistogramAnalyzer5.cxx
done
sed -i "22s/${arr2[20]}/${arr2[0]}/" HistogramAnalyzer5.cxx
sed -i "24s/${arr2[20]}/${arr2[0]}/" HistogramAnalyzer5.cxx
sed -i "12s/60/40/" HistogramAnalyzer5.cxx
sed -i "13s/70/50/" HistogramAnalyzer5.cxx
#change back histogram names
sed -i "22s/Gam${DoubleGams[6]}/Gam${DoubleGams[0]}/" HistogramAnalyzer5.cxx
sed -i "24s/Gam${DoubleGams[6]}/Gam${DoubleGams[0]}/" HistogramAnalyzer5.cxx
#Change back storage folder
sed -i "26s/Gam${DoubleGams[6]}/Gam${DoubleGams[0]}/" HistogramAnalyzer5.cxx
sed -i "201s/Gam${DoubleGams[6]}/Gam${DoubleGams[0]}/" HistogramAnalyzer5.cxx

