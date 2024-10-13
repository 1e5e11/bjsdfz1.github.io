set fso=createobject("Scripting.FileSystemObject")

set d = fso.OpenTextFile("whitelist.json")
ydb="  {""uuid"": ""6fbbf6fc-9706-39bc-b455-debf6d7c88f0"",""name"": ""az""}]"

For Each ar In WScript.Arguments
cd=ar
next

if cd="" then

do
dshcbsdc=inputbox("输入你的id和uuid，用"",""隔开。")
if dshcbsdc="" then
exit do
end if
uname=split(dshcbsdc,",")(0)
uuid=split(dshcbsdc,",")(1)
if FindCount(uuid,"-")<4 or FindCount(uuid,"-")>4 or len(uuid)>36 or len(uuid)<36 then
msgbox "not uuid"
exit do
end if
ysnr=d.readall
ysdm=left(ysnr,len(ysnr)-64)
ysdm=ysdm&vbLf&"  {""uuid"": """
ysdm=ysdm&uuid&""",    ""name"": """&uname&"""  },"&vbLf
set w = fso.OpenTextFile("whitelist.json",2)
w.Write ysdm&ydb
set w=nothing


loop


else

uname=split(cd,",")(0)
uuid=split(cd,",")(1)
if FindCount(uuid,"-")<4 or FindCount(uuid,"-")>4 or len(uuid)>36 or len(uuid)<36 then
else
ysnr=d.readall
ysdm=left(ysnr,len(ysnr)-64)
ysdm=ysdm&vbLf&"  {""uuid"": """
ysdm=ysdm&uuid&""",    ""name"": """&uname&"""  },"&vbLf
set w = fso.OpenTextFile("whitelist.json",2)
w.Write ysdm&ydb
set w=nothing

end if



end if










Function FindCount(Str,toSearch)
Dim Times,WordLen
Times = 0
WordLen = Len(toSearch)
For i = 1 To Len(Str)+1-WordLen
If Mid(Str,i,WordLen) = toSearch Then
Times = Times + 1
End If
Next
FindCount = Times
end function