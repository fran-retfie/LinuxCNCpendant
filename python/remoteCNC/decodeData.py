


def decodeData(rawData):
    Data = {}
    Data['jogButtons'] = rawData[1]
    Data['Buttons'] = rawData[2] + rawData[3]*256
    Data['Pot0'] = (rawData[4] + rawData[5]*256)*100//4096
    Data['Pot1'] = (rawData[6] + rawData[7]*256)*100//4096
    Data['Pot2'] = (rawData[8] + rawData[9]*256)*100//4096
    Data['Pot3'] = (rawData[10] + rawData[11]*256)*100//4096
    Data['JogX'] = (rawData[12] + rawData[13]*256)*100//4096
    Data['JogY'] = (rawData[14] + rawData[15]*256)*100//4096
    Data['JogZ'] = (rawData[16] + rawData[17]*256)*100//4096
    Data['JogA'] = (rawData[18] + rawData[19]*256)*100//4096

    return Data
