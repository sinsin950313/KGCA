echo "n" | cp -r -i Project/Resource/ Naver\ MYBOX/EngineData/

for Directory in Unreal/*/;
do
	ProjectName="$(basename $Directory)"

	for SubDirectory in Unreal/$ProjectName/Content/*;
	do
		NewName="$(basename $SubDirectory)"
		if [ -f $SubDirectory ];
		then
			mkdir -p Naver\ MYBOX/UnrealData/$ProjectName/Content/
			echo "n" | cp -r -i Unreal/$ProjectName/Content/$NewName Naver\ MYBOX/UnrealData/$ProjectName/Content/
		elif [ "$NewName" != "Blueprint" ];
		then
			mkdir -p Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName
			echo "n" | cp -r -i Unreal/$ProjectName/Content/$NewName Naver\ MYBOX/UnrealData/$ProjectName/Content/$NewName
		fi
	done
done
