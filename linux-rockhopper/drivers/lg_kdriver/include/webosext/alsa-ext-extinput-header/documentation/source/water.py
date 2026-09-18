import PyPDF2
from PyPDF2.generic import DecodedStreamObject, NameObject, DictionaryObject, createStringObject, ArrayObject
'''
image1 = Image.open('/home/lge123/linuxtv-ext-header/Documentation/source/water.PNG')
print(image1.mode)
image_inv = ImageOps.invert(image1)
inv_l = image_inv.convert('L')
image1.putalpha(inv_l)
image1.save('/home/lge123/linuxtv-ext-header/Documentation/source/convert.PNG')

wow = Image.open('/home/lge123/linuxtv-ext-header/Documentation/source/convert.PNG')
print(wow.mode)
im1 = wow.convert('RGB')

im1.save('/home/lge123/linuxtv-ext-header/Documentation/source/mark.pdf')
'''
from reportlab.pdfgen import canvas
from reportlab.lib.units import cm
import os

def appendAttachment(myPdfFileWriterObj, fname, fdata):
    # The entry for the file
    file_entry = DecodedStreamObject()
    file_entry.setData(fdata)
    file_entry.update({NameObject("/Type"): NameObject("/EmbeddedFile")})

    # The Filespec entry
    efEntry = DictionaryObject()
    efEntry.update({ NameObject("/F"):file_entry })

    filespec = DictionaryObject()
    filespec.update({NameObject("/Type"): NameObject("/Filespec"),NameObject("/F"): createStringObject(fname),NameObject("/EF"): efEntry})

    if "/Names" not in myPdfFileWriterObj._root_object.keys():
        # No files attached yet. Create the entry for the root, as it needs a reference to the Filespec
        embeddedFilesNamesDictionary = DictionaryObject()
        embeddedFilesNamesDictionary.update({NameObject("/Names"): ArrayObject([createStringObject(fname), filespec])})

        embeddedFilesDictionary = DictionaryObject()
        embeddedFilesDictionary.update({NameObject("/EmbeddedFiles"): embeddedFilesNamesDictionary})
        myPdfFileWriterObj._root_object.update({NameObject("/Names"): embeddedFilesDictionary})
    else:
        # There are files already attached. Append the new file.
        myPdfFileWriterObj._root_object["/Names"]["/EmbeddedFiles"]["/Names"].append(createStringObject(fname))
        myPdfFileWriterObj._root_object["/Names"]["/EmbeddedFiles"]["/Names"].append(filespec)


if __name__ == "__main__":
	content="LGE Confidential"
	page= canvas.Canvas('source/resources/mark.pdf', pagesize = (21*cm, 29.7*cm))
	page.translate(18.0*cm, 0.0*cm)
	page.setFont("Helvetica", 12)
	#page.rotate(45)
	page.setFillColorRGB(0.55,0.55,0.55)
	page.setFillAlpha(0.3)
	page.drawString(-1*cm, 1*cm, content)
	page.save()

	linux_pdf = open('build/singlepage.pdf','rb')
	reader = PyPDF2.PdfFileReader(linux_pdf)
	number_of_pages = reader.numPages
	print(number_of_pages)
	mark_pdf = open('source/resources/mark.pdf','rb')
	mark = PyPDF2.PdfFileReader(mark_pdf) 

	merged_pdf = PyPDF2.PdfFileWriter()

	for i in range(number_of_pages):
		ori = reader.getPage(i)
		ori.mergePage(mark.getPage(0))
		merged_pdf.addPage(ori)

	download_path = "build/singlehtml/_downloads"
	file_list = []

	for (root, directories, files) in os.walk(download_path):
		for file in files:
			file_list.append(os.path.join(root, file))

	print(file_list)

	for file in file_list:
		file_name = ""
		with open(file,'rb') as data:
			file_name = file.split('/')[-1]
			print(file_name)
		#merged_pdf.addAttachment(file_name,data.read())
			appendAttachment(merged_pdf, file_name, data.read())

	result = open('build/merged_singlepage.pdf','wb')
	merged_pdf.write(result)

	result.close()
	linux_pdf.close()
	mark_pdf.close()


