mkdir -p Naver\ MYBOX/EngineData/
echo "n" | cp -r -i -v Project/Resource/ Naver\ MYBOX/EngineData/

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

			if [ "$NewName" == "Map" ];
			then
				cp -r -f -v Unreal/$ProjectName/Content/$NewName Naver\ MYBOX/UnrealData/$ProjectName/Content/
			else
				echo "n" | cp -r -i -v Unreal/$ProjectName/Content/$NewName Naver\ MYBOX/UnrealData/$ProjectName/Content/
			fi
		fi
	done
done
