function LuaExportStart()

	package.path  = package.path..";"..lfs.currentdir().."/LuaSocket/?.lua"
	package.cpath = package.cpath..";"..lfs.currentdir().."/LuaSocket/?.dll"

	socket = require("socket")
	IPAddress = "127.0.0.1"
	Port = 6969

	MySocket = socket.try(socket.connect(IPAddress, Port))
	MySocket:setoption("tcp-nodelay",true) 
end

function LuaExportBeforeNextFrame()
end

function LuaExportAfterNextFrame()
end

function LuaExportStop()

	if MySocket then 
		socket.try(MySocket:send("exit"))
		MySocket:close()
	end
end

function LuaExportActivityNextEvent(t)
	local tNext = t
	local BALT = LoGetAltitudeAboveSeaLevel()
	local IAS = LoGetIndicatedAirSpeed()				--IAS m/s
	local pitch, bank, yaw = LoGetADIPitchBankYaw()
	socket.try(MySocket:send(string.format("%.2f, %.2f, %.2f, %.2f\n",
											BALT,		--Altimeter
											IAS,		--Speed Indicator
											pitch,		--Turn Coordinator[0]
											bank		--Turn Coordinator[1]
											)))
	tNext = tNext + 0.3
	return tNext
end