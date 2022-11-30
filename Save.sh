echo "n" | cp -r -i Project/Resource/ Naver\ MYBOX/EngineData/

for dir in Unreal/*/;
do
name="$(basename $dir)"
echo "n" | cp -r -i Unreal/$name/Content/ Naver\ MYBOX/UnrealData/$name
done
