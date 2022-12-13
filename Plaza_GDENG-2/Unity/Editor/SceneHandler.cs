using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.Xml;

[ExecuteInEditMode]

[CustomEditor(typeof(ObjectCreator))]
public class SceneReader : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();

        ObjectCreator myObjectCreator = (ObjectCreator)target;

        if (GUILayout.Button("Load XML File"))
        {
            myObjectCreator.CreateObject();
        }

        if (GUILayout.Button("Save XML File"))
        {
            myObjectCreator.SaveXML();
        }
    }
}
