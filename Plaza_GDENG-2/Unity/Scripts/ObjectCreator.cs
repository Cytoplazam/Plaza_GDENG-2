using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Xml;
using System;
using UnityEngine.Windows;

[ExecuteInEditMode]
public class ObjectCreator : MonoBehaviour
{
    XmlDocument itemDataXml;

    [SerializeField] private TextAsset xmlTextAsset;

    private void Awake()
    {
        itemDataXml = new XmlDocument();
        itemDataXml.LoadXml(xmlTextAsset.text);

        //CreateObject();
    }
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SaveXML()
    {
        GameObject[] objs = GameObject.FindGameObjectsWithTag("EditorOnly");
        GameObject[] objsUnity = GameObject.FindGameObjectsWithTag("Finish");
        //Debug.Log(objs.Length);

        XmlDocument saveFile = new XmlDocument();

        if (objs.Length == 0)
            objs = objsUnity;
        XmlNode root = saveFile.CreateElement("GameObjects");
        saveFile.AppendChild(root);

        for (int i = 0; i < objs.Length; i++)
        {
            Debug.Log("saved a " + objs[i].name);
            XmlNode obj = saveFile.CreateElement("GameObject");
            string name = objs[i].name;
            int type = 0;

            float posX = objs[i].transform.position.x;
            float posY = objs[i].transform.position.y;
            float posZ = objs[i].transform.position.z;

            float rotX = objs[i].transform.rotation.eulerAngles.x;
            float rotY = objs[i].transform.rotation.eulerAngles.y;
            float rotZ = objs[i].transform.rotation.eulerAngles.z;

            float scaleX = objs[i].transform.localScale.x;
            float scaleY = objs[i].transform.localScale.y;
            float scaleZ = objs[i].transform.localScale.z;

            if (objs[i].name.Contains("Cube"))
            {
                if (objs[i].name.Contains("PhysicsCube"))
                    type = 2;
                else type = 1;
            }
            else if (objs[i].name.Contains("Plane") || objs[i].name.Contains("plane"))
            {
                if (objs[i].name.Contains("PhysicsPlane"))
                    type = 4;
                else type = 3;
            }
            else if (objs[i].name.Contains("Sphere"))
            {
                if (objs[i].name.Contains("PhysicsSphere"))
                    type = 6;
                else type = 5;
            }
            else if (objs[i].name.Contains("Capsule"))
            {
                if (objs[i].name.Contains("PhysicsCapsule"))
                    type = 8;
                else type = 7;
            }

            XmlNode objName = saveFile.CreateElement("Name");
            objName.InnerText = name;

            obj.AppendChild(objName);

            XmlNode objType = saveFile.CreateElement("Type");
            objType.InnerText = type.ToString();

            obj.AppendChild(objType);

            XmlNode objPos = saveFile.CreateElement("Position");
            XmlNode oPX = saveFile.CreateElement("x");
            XmlNode oPY = saveFile.CreateElement("y");
            XmlNode oPZ = saveFile.CreateElement("z");

            oPX.InnerText = posX.ToString();
            oPY.InnerText = posY.ToString();
            oPZ.InnerText = posZ.ToString();

            objPos.AppendChild(oPX);
            objPos.AppendChild(oPY);
            objPos.AppendChild(oPZ);

            obj.AppendChild(objPos);

            XmlNode objRot = saveFile.CreateElement("Rotation");
            XmlNode oRX = saveFile.CreateElement("x");
            XmlNode oRY = saveFile.CreateElement("y");
            XmlNode oRZ = saveFile.CreateElement("z");

            oRX.InnerText = rotX.ToString();
            oRY.InnerText = rotY.ToString();
            oRZ.InnerText = rotZ.ToString();

            objRot.AppendChild(oRX);
            objRot.AppendChild(oRY);
            objRot.AppendChild(oRZ);

            obj.AppendChild(objRot);

            XmlNode objScale = saveFile.CreateElement("Scale");
            XmlNode oSX = saveFile.CreateElement("x");
            XmlNode oSY = saveFile.CreateElement("y");
            XmlNode oSZ = saveFile.CreateElement("z");

            oSX.InnerText = scaleX.ToString();
            oSY.InnerText = scaleY.ToString();
            oSZ.InnerText = scaleZ.ToString();

            objScale.AppendChild(oSX);
            objScale.AppendChild(oSY);
            objScale.AppendChild(oSZ);

            obj.AppendChild(objScale);

            root.AppendChild(obj);
        }

        saveFile.Save(Application.dataPath + "/test.xml");

        if (File.Exists(Application.dataPath + "/test.xml"))
        {
            Debug.Log("XML Saved!");
        }
    }

    public void CreateObject()
    {
        XmlNodeList objects = itemDataXml.SelectNodes("/GameObjects/GameObject");   

        foreach (XmlNode item in objects)
        {
            AGameObject newGameObject = new AGameObject(item);
        }
    }

    class AGameObject
    {
        public string name { get; private set; }
        public int type { get; private set; }
        public Vector3 pos { get; private set; }
        public Vector3 rot { get; private set; }
        public Vector3 scale { get; private set; }

        public AGameObject(XmlNode curItemNode)
        {
            name = curItemNode["Name"].InnerText;
            type = int.Parse(curItemNode["Type"].InnerText);

            XmlNode posNode = curItemNode.SelectSingleNode("Position");

            float posX = float.Parse(posNode["x"].InnerText);
            float posY = float.Parse(posNode["y"].InnerText);
            float posZ = float.Parse(posNode["z"].InnerText);

            pos = new Vector3(posX, posY, posZ);

            XmlNode rotNode = curItemNode.SelectSingleNode("Rotation");

            float rotX = float.Parse(rotNode["x"].InnerText);
            float rotY = float.Parse(rotNode["y"].InnerText);
            float rotZ = float.Parse(rotNode["z"].InnerText);

            rot = new Vector3(rotX, rotY, rotZ);

            XmlNode scaNode = curItemNode.SelectSingleNode("Scale");

            float scaX = float.Parse(scaNode["x"].InnerText);
            float scaY = float.Parse(scaNode["y"].InnerText);
            float scaZ = float.Parse(scaNode["z"].InnerText);

            scale = new Vector3(scaX, scaY, scaZ);

            GameObject obj;

            if (type == 1)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Cube);
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot) ;
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
            if (type == 2)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Cube);
                Rigidbody rb = obj.AddComponent<Rigidbody>();
                rb.mass = 5;
                rb.isKinematic = false;
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot);
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
            else if (type == 3)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Plane);
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot);
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
            if (type == 4)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Plane);
                Rigidbody rb = obj.AddComponent<Rigidbody>();
                rb.mass = 5;
                rb.isKinematic = true;
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot);
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
            if (type == 5)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Sphere);
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot);
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
            if (type == 6)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Sphere);
                Rigidbody rb = obj.AddComponent<Rigidbody>();
                rb.mass = 5;
                rb.isKinematic = false;
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot);
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
            if (type == 7)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Capsule);
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot);
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
            if(type == 8)
            {
                obj = GameObject.CreatePrimitive(PrimitiveType.Capsule);
                Rigidbody rb = obj.AddComponent<Rigidbody>();
                rb.mass = 5;
                rb.isKinematic = false;
                obj.name = name;
                obj.transform.position = pos;
                obj.transform.rotation = Quaternion.Euler(rot);
                obj.transform.localScale = scale;
                obj.tag = "EditorOnly";
            }
        }
    }
}
