from flask import Flask, redirect, render_template, request
import pdfkit


app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "POST":
        name = request.form.get("name")
        age = request.form.get("age")
        email = request.form.get("email")
        job = request.form.get("job")
        linkedin = request.form.get("linkedin")
        phone = request.form.get("phone")
        nacionalidade=request.form.get("nacionalidade")
        city=request.form.get("city")


        objetivo=request.form.get("objetivo")


        skills = []
        skill = request.form.get("skill")
        skill1 = request.form.get("skill1")
        skill2 = request.form.get("skill2")
        skill3 = request.form.get("skill3")
        skill4 = request.form.get("skill4")
        skill5 = request.form.get("skill5")
        skill6 = request.form.get("skill6")
        skill7 = request.form.get("skill7")
        skill8 = request.form.get("skill8")
        skill9 = request.form.get("skill9")



        experiencias = []
        cargo1 = {}
        if request.form.get("cargo") != "":
            cargo1["cargo"] = request.form.get("cargo")
            cargo1["company"] = request.form.get("company")
            cargo1["start"] = request.form.get("start")
            cargo1["end"] = request.form.get("end")
            cargo1["description"] = request.form.get("description")
            experiencias.append(cargo1)

        if request.form.get("cargo1") != "":
            cargo2={}
            cargo2["cargo"] = request.form.get("cargo1")
            cargo2["company"] = request.form.get("company1")
            cargo2["start"] = request.form.get("start1")
            cargo2["end"] = request.form.get("end1")
            cargo2["description"] = request.form.get("description1")
            experiencias.append(cargo2)

        if request.form.get("cargo2") != "":
            cargo3={}
            cargo3["cargo"] = request.form.get("cargo2")
            cargo3["company"] = request.form.get("company2")
            cargo3["start"] = request.form.get("start2")
            cargo3["end"] = request.form.get("end2")
            cargo3["description"] = request.form.get("description2")
            experiencias.append(cargo3)

        if request.form.get("cargo3") != "":
            cargo4={}
            cargo4["cargo"] = request.form.get("cargo3")
            cargo4["company"] = request.form.get("company3")
            cargo4["start"] = request.form.get("start3")
            cargo4["end"] = request.form.get("end3")
            cargo4["description"] = request.form.get("description3")
            experiencias.append(cargo4)



        universitys = []
        curso1 = {}
        if request.form.get("university") != "":
            curso1["university"] = request.form.get("university")
            curso1["degree"] = request.form.get("degree")
            curso1["desc"] = request.form.get("desc")
            universitys.append(curso1)

        if request.form.get("university1") != "":
            curso2={}
            curso2["university"] = request.form.get("university1")
            curso2["degree"] = request.form.get("degree1")
            curso2["desc"] = request.form.get("desc1")
            universitys.append(curso2)

        if request.form.get("university2") != "":
            curso3={}
            curso3["university"] = request.form.get("university2")
            curso3["degree"] = request.form.get("degree1")
            curso3["desc"] = request.form.get("desc2")
            universitys.append(curso3)
        print(universitys)



        if request.form.get("check") == "Student":
            return render_template("resume2.html", name=name, job=job, email=email, age=age, phone=phone, linkedin=linkedin,nacionalidade=nacionalidade, city=city,
                objetivo=objetivo, skill=skill, skill1=skill1,skill2=skill2,skill3=skill3,skill4=skill4,skill5=skill5,skill6=skill6,skill7=skill7,skill8=skill8,skill9=skill9,
                experiencias=experiencias, universitys=universitys)



        return render_template("resume.html", name=name, job=job, email=email, age=age, phone=phone, linkedin=linkedin,nacionalidade=nacionalidade, city=city,
                objetivo=objetivo, skill=skill, skill1=skill1,skill2=skill2,skill3=skill3,skill4=skill4,skill5=skill5,skill6=skill6,skill7=skill7,skill8=skill8,skill9=skill9,
                experiencias=experiencias, universitys=universitys)


    else:
        return render_template("index.html")


