# Digit Identify

פרויקט זיהוי ספרות בעזרת למידת מכונה, בשפת Python.  
המערכת משתמשת במודל קלאסיפיקציה מבוסס `KNeighborsClassifier` על מנת לזהות ספרות מתוך מערך הנתונים של ספרות ידניות (`sklearn.datasets.load_digits`).

## 🧠 תיאור הפרויקט

- שימוש ב־scikit-learn לצורך טעינת דאטהסט של תמונות ספרות בגודל 8x8 פיקסלים.
- בניית מודל KNN פשוט ללמידת הספרות.
- הדמיית תוצאות התחזית על תמונות מספריות אמיתיות.
- הדגמת ביצועי המודל על נתונים חדשים (test set).

## 🛠 טכנולוגיות וכלים

- Python 3  
- NumPy  
- scikit-learn  
- Matplotlib

## ▶️ איך להריץ

1. ודאו כי מותקנות הספריות הבאות:
    ```bash
    pip install numpy scikit-learn matplotlib
    ```
2. הריצו את הקובץ:
    ```bash
    python main.py
    ```
