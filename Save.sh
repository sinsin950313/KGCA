mkdir -p Naver\ MYBOX/EngineData/
if [ "$1" == "-f" ]
then
	cp -r -u -v Project/Resource/ Naver\ MYBOX/EngineData/
else
	echo "n" | cp -r -i -v Project/Resource/ Naver\ MYBOX/EngineData/
fi

for Directory in Unreal/*/;
do
	ProjectName="$(basename $Directory)"
	mkdir -p Naver\ MYBOX/UnrealData/$ProjectName/Content

	for SubDirectory in Unreal/$ProjectName/Content/*;
	do
		NewName="$(basename $SubDirectory)"
		if [ "$NewName" != "Blueprint" ];
		then
#			if [ -d $SubDirectory ];
#			then
#				mkdir -p Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName
#			fi

			if [ "$1" == "-f" ]
			then
				cp -r -u -v Unreal/$ProjectName/Content/$NewName Naver\ MYBOX/UnrealData/$ProjectName/Content/
			else
				if [ "$NewName" == "Map" ];
				then
					cp -r -f -v Unreal/$ProjectName/Content/$NewName Naver\ MYBOX/UnrealData/$ProjectName/Content/
				else
					echo "n" | cp -r -v -i Unreal/$ProjectName/Content/$NewName Naver\ MYBOX/UnrealData/$ProjectName/Content/
				fi
			fi
		fi
	done
done
