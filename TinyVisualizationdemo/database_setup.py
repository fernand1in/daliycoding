import sqlite3

def create_database_and_table():
    # 创建或连接到数据库文件
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    # 创建用户表
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            email TEXT,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    ''')

    # 提交更改并关闭连接
    conn.commit()
    conn.close()

if __name__ == '__main__':
    create_database_and_table()
    print("数据库和用户表创建成功！")