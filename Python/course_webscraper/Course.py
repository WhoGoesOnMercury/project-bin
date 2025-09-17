import undetected_chromedriver as uc
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

# Anything gathered from this URL is available to everyone
URL = "https://enroll.dlsu.edu.ph/dlsu/view_course_offerings"
# Include vaid ID number here
ID_NO = 0
TIMEOUT = 10 
COURSE_CODES = ["STMETHD", "STDISCM", "CCINOV8", "GEWORLD", "LCFAITH", "GEETHIC"]

def getCourseList(driver, course_code):
    try:
        # Wait until table is present
        table = WebDriverWait(driver, TIMEOUT).until(
            EC.presence_of_element_located((By.XPATH, "//table[@border='0' and @align='CENTER']"))
        )

        rows = table.find_elements(By.TAG_NAME, "tr")
        data_lines = []

        for row in rows:
            cells = row.find_elements(By.TAG_NAME, "td")
            cell_texts = [cell.text.strip() for cell in cells]
            data_lines.append("\t".join(cell_texts))

        # Save to file (append mode)
        with open("course_list.txt", "a", encoding="utf-8") as f:
            f.write(f"\n=== {course_code} ===\n")
            for line in data_lines:
                f.write(line + "\n")

        print(f"Saved data for {course_code}")
    except Exception as e:
        print(f"Error retrieving table for {course_code}: {e}")

options = uc.ChromeOptions()
options.add_argument("--start-maximized")
driver = uc.Chrome(options=options)

try:
    driver.get(URL)

    WebDriverWait(driver, TIMEOUT).until(
        EC.presence_of_element_located((By.NAME, "p_id_no"))
    )

    driver.find_element(By.NAME, "p_id_no").send_keys(ID_NO)
    driver.find_element(By.NAME, "p_button").click()

    WebDriverWait(driver, TIMEOUT).until(
        EC.presence_of_element_located((By.NAME, "p_course_code"))
    )

    for code in COURSE_CODES:
        course_input = driver.find_element(By.NAME, "p_course_code")
        course_input.clear()
        course_input.send_keys(code)
        driver.find_element(By.NAME, "p_button").click()

        getCourseList(driver, code)

        time.sleep(2)

finally:
    driver.quit()
