import json

data = '''
{
    "age": 16,
    "name": "张三",
    "like": "打电动"
}
'''

data :dict = json.loads(data)
print(data['age'])
