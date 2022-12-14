#echo "n" | cp -r -i -v Naver\ MYBOX/EngineData/Resource Project
cp -r -u -v Naver\ MYBOX/EngineData/Resource Project

for Directory in Naver\ MYBOX/UnrealData/*;
do
	ProjectName="$(basename "$Directory")"
	mkdir -p Unreal/$ProjectName/Content/

	for SubDirectory in Naver\ MYBOX/UnrealData/$ProjectName/Content/*
	do
		NewName="$(basename "$SubDirectory")"
#		if [ -d "$SubDirectory" ];
#		then
#			mkdir -p Unreal/$ProjectName/Content/$NewName
#		fi

			cp -r -u -v Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName Unreal/$ProjectName/Content/

#		if [ "$NewName" == "Map" ];
#		then
#			cp -r -f -v Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName Unreal/$ProjectName/Content/
#		else
#			echo "n" | cp -r -i -v Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName Unreal/$ProjectName/Content/
#		fi
	done
done
