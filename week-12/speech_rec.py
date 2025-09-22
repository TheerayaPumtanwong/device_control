# import re, speech_recognition as sr

# r = sr.Recognizer()
# with sr.Microphone() as mic:
#     r.adjust_for_ambient_noise(mic, duration=0.6)
#     print("พูดว่า 'สวัสดี' เช่น 'หมุน มอเตอร์ไปที่ 90 องศา'")
    
#     while True:
#       try:
#           audio = r.listen(mic, timeout=6, phrase_time_limit=10)
#           text = r.recognize_google(audio, language="th-TH")
#           print("ได้ยิน :",text)
          
#           if text.startswith("สวัสดี ธีรยา"):
#               cmd = text.replace("สวัสดี ธีรยา", "", 1).strip()
#               m = re.search(r"(\d+)", cmd)
#               angle = int(m.group(1)) if m else None
#               print("สวัสดี ธีรยา : ", cmd, "| มุม :", angle)
              
#       except sr.WaitTimeoutError:
#         print("ไม่มีเสียงพูดมาได้เลยค่ะ")
        
        
#       except sr.UnknownValueError:
#         print("พูดมาได้เลยค่ะ")

# import re, speech_recognition as sr

# r = sr.Recognizer()
# with sr.Microphone() as mic:
#     r.adjust_for_ambient_noise(mic, duration=0.6)
#     print("พูดว่า 'สวัสดี' เช่น 'สวัสดี รวม 12 7 5' ")

#     while True:
#         try:
#             audio = r.listen(mic, timeout=6, phrase_time_limit=10)
#             text = r.recognize_google(audio, language="th-TH") 
#             print("ได้ยิน :", text)
           
#             if text.startswith("สวัสดี รวม"):
#                 numbers = re.findall(r"\d+", text)  # ดึงตัวเลขทั้งหมด
#                 nums = list(map(int, numbers)) if numbers else []
#                 if nums:
#                     total = sum(nums)
#                     avg = total / len(nums)
#                     print(f"TH → SUM={total} AVG={avg:.2f}")
#                 else:
#                     print("ไม่เจอตัวเลขเลยค่ะ")

           
           

#         except sr.WaitTimeoutError:
#             print("ไม่มีเสียงพูดมาได้เลยค่ะ")

#         except sr.UnknownValueError:
#             print("พูดมาได้เลยค่ะ")


import re, speech_recognition as sr


r = sr.Recognizer()
with sr.Microphone() as mic:
    r.adjust_for_ambient_noise(mic, duration=0.6)
    print("พูดว่า 'สวัสดี รวม 12 7 5' หรือ 'สวัสดี รวม สิบสอง เจ็ด ห้า'")

    while True:
        try:
            audio = r.listen(mic, timeout=6, phrase_time_limit=10)
            text = r.recognize_google(audio, language="th-TH") 
            print("ได้ยิน :", text)

            # เช็คว่ามีคำว่า "รวม" ในประโยค
            if "รวม" in text:
                parts = text.replace("สวัสดี", "").replace("รวม", "").strip().split()
                nums = []

                for p in parts:
                    if p.isdigit():
                        nums.append(int(p))
                    else:
                        try:
                            nums.append(thai_str_to_num(p))
                        except:
                            pass

                if nums:
                    total = sum(nums)
                    avg = total / len(nums)
                    print(f"SUM={total} AVG={avg:.2f}")
                else:
                    print("⚠ ไม่เจอตัวเลขเลยค่ะ")

        except sr.WaitTimeoutError:
            print("ไม่มีเสียงพูดมาได้เลยค่ะ")

        except sr.UnknownValueError:
            print("พูดมาได้เลยค่ะ")
            
