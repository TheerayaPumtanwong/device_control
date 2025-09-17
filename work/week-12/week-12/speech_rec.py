import re, time, speech_recognition as sr

r = sr.Recognizer()
with sr.Microphone() as mic:
    r.adjust_for_ambient_noise(mic, duration=0.6)
    print("พูดว่า 'สวัสดีแพรวา ตั้งเวลา ... วินาที' เช่น 'สวัสดีแพรวา ตั้งเวลา 5 วินาที'")
    
    while True:
        try:
            audio = r.listen(mic, timeout=6, phrase_time_limit=10)
            text = r.recognize_google(audio, language="th-TH")
            print("ได้ยิน :", text)
            
            if text.startswith("สวัสดีแพรวา"):
                cmd = text.replace("สวัสดีแพรวา", "", 1).strip()
                m = re.search(r"(\d+)", cmd)
                seconds = int(m.group(1)) if m else None

                print("สวัสดีค่ะแพรวา ยินดีที่ได้ยินเสียงนะคะ ")

                if seconds:
                    print(f"เริ่มนับถอยหลัง {seconds} วินาที")
                    for i in range(seconds, 0, -1):
                        print(i)
                        time.sleep(1)
                    print("หมดเวลาแล้วค่ะ")
                else:
                    print("ไม่เจอตัวเลขวินาทีค่ะ")
                
        except sr.WaitTimeoutError:
            print("ไม่มีเสียงพูดมาได้เลยค่ะ")
            
        except sr.UnknownValueError:
            print("พูดมาได้เลยค่ะ......")
