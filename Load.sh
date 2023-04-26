if [ "$1" == "-f" ]
then
	cp -r -u -v Naver\ MYBOX/EngineData/Resource Project
else
	echo "n" | cp -r -i -v Naver\ MYBOX/EngineData/Resource Project
fi

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

		if [ "$1" == "-f" ]
		then
			cp -r -u -v Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName Unreal/$ProjectName/Content/
		else
			if [ "$NewName" == "Map" ];
			then
				cp -r -f -v Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName Unreal/$ProjectName/Content/
			else
				echo "n" | cp -r -i -v Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName Unreal/$ProjectName/Content/
			fi
		fi
	done
done
